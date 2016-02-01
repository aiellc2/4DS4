// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// This is the embedded software for the
// LCD / Camera design

#include <stdio.h>
#include "io.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "priv/alt_busy_sleep.h"

#define NUM_LINES 480
#define LINE_LEN 640

void TouchPanel_int(int *filter_flag) {
    static int exposure = 0x0400, run = 1;
    int TP_val, x_val, y_val, key = 6;

    TP_val = IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 0);
    x_val = (TP_val >> 20) & 0xFF; y_val = (TP_val >> 4) & 0xFF;

    if (((TP_val >> 31) & 0x1) && (x_val >= 0xC9) && (x_val <= 0xF1)) {
        if ((y_val >= 0x17) && (y_val <= 0x33)) { // Key 0
            key = 0;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x1);
        }
        if ((y_val >= 0x3D) && (y_val <= 0x58)) { // Key 1
            key = 1;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x2);
        }
        if ((y_val >= 0x62) && (y_val <= 0x7E)) { // Key 2
            key = 2;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x4);
        }
        if ((y_val >= 0x88) && (y_val <= 0xA4)) { // Key 3
            key = 3;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x8);
        }
        if ((y_val >= 0xAE) && (y_val <= 0xC9)) { // Key 4
            key = 4;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x10);
        }
        if ((y_val >= 0xD3) && (y_val <= 0xEF)) { // Key 5
            key = 5;
            IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x20);
        }
    } else IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 0, 0x0);
    
    if (IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2) & 0x2) { // posedge
        switch (key) {
            case 0 : 
                if (run == 1) {
                    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8);
                    run = 0;
                } else {
                    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x4);
                    run = 1;
                }
                break;
            case 1 : 
                *filter_flag = 1;
                run = 0;
                break;
            case 4 : 
                if (exposure <= 0xFEFF) exposure += 0x0100;
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, exposure);
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
                break;                              
            case 5 : 
                if (exposure >= 0x0100) exposure -= 0x0100;
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, exposure);
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
                break;
        }
    }
    
    TP_val = IORD(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2, TP_val & 0x30);
}

void Switch_Nios_Mode() {
    alt_u32 status;

    alt_printf("Changing SDRAM to NIOS mode\n");    
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8); // camera stop
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1, 0x1F); // resync read and write pipe
    status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);
    while (((status >> 2) & 0x7) != 5) {
        status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);        
        alt_busy_sleep(10);
    }
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1, 0x03); // SDRAM read/write load to nios    
    status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);
    while (((status >> 2) & 0x7) != 4) {
        status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);        
        alt_busy_sleep(10);
    }
    alt_printf("SDRAM changed to NIOS mode\n"); 
}

void Switch_HW_Mode() {
    alt_u32 status;
        
    alt_printf("Changing SDRAM to HW mode\n");
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1, 0x1C); // resync read and write pipe
    status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);
    while (((status >> 2) & 0x7) != 5) {
        status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);        
        alt_busy_sleep(10);
    }
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1, 0x0); // LCD reset
    status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);
    while (((status >> 2) & 0x7) != 4) {
        status = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 1);        
        alt_busy_sleep(10);
    }
    alt_printf("SDRAM changed to HW mode\n");    
}    

void Read_Image_Line(
    alt_u8 *R_vals, alt_u8 *G_vals, alt_u8 *B_vals
) {
    int k; alt_u32 raw_rgb;

    for (k = 0; k < LINE_LEN; k++) {
        raw_rgb = IORD(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 0);
        R_vals[k] = (raw_rgb >> 2) & 0xFF;
        G_vals[k] = ((raw_rgb >> 12) & 0x7) | ((raw_rgb >> 23) & 0xF8); 
        B_vals[k] = ((raw_rgb >> 18) & 0xFF);
    }
}

void Write_Image_Line(
    alt_u8 *R_vals, alt_u8 *G_vals, alt_u8 *B_vals
) {
    int k; alt_u32 raw_rgb;

    for (k = 0; k < LINE_LEN; k++) {
        raw_rgb = 
            (R_vals[k] << 2 ) | ((G_vals[k] & 0x7) << 12) | 
            (B_vals[k] << 18) | ((G_vals[k] & 0xF8) << 23);        
        IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 0, raw_rgb);
    }
}

void Y_conversion() {
    int i, j, Y;
    alt_u8 R_vals[LINE_LEN], G_vals[LINE_LEN], B_vals[LINE_LEN];

    printf("Starting Y conversion...\n");
    
    for (i = 0; i < NUM_LINES; i++) {
        Read_Image_Line(R_vals, G_vals, B_vals);
        for (j = 0; j < LINE_LEN; j++) {
            Y = (1052 * R_vals[j] + 2064 * G_vals[j] + 401 * B_vals[j]) >> 12;
            R_vals[j] = G_vals[j] = B_vals[j] = Y;
        }
        
        Write_Image_Line(R_vals, G_vals, B_vals);
    }

    printf("Y conversion complete\n");
}

int main()
{
    volatile int filter_flag = 0;

    alt_irq_register(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_IRQ, (void *)&filter_flag, (void *)TouchPanel_int);

    printf("Experiment 2!\n");

    // initialize touch panel
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2, 0x0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 1, 0x400000);

    // initialize camera
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, 0x0400);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
    while ((IORD(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1) & 0x1) == 0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x4);

    // initialize buttons
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 1, 0x0);

    while (1) {
        if (filter_flag) {
            Switch_Nios_Mode();
            Y_conversion();
            Switch_HW_Mode();
            filter_flag = 0;
        }
    }

    return 0;
}
