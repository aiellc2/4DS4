// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

void translate_PS2_code(PS2_buffer_struct *PS2_buffer_data, int PS2_code) {
	if (PS2_buffer_data->cur_buf_length >= MAX_STRING_LENGTH-2) {
		printf("buffer overflow\n");
	} else {
		switch (PS2_code) {
			case 0x0E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '`'; break;
			case 0x16: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '1'; break;
			case 0x1E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '2'; break;
			case 0x26: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '3'; break;
			case 0x25: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '4'; break;
			case 0x2E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '5'; break;
			case 0x36: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '6'; break;
			case 0x3D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '7'; break;
			case 0x3E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '8'; break;
			case 0x46: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '9'; break;
			case 0x45: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '0'; break;
			case 0x4E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '-'; break;
			case 0x55: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '='; break;
	
			case 0x5D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '\\'; break;
			case 0x15: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'q'; break;
			case 0x1D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'w'; break;
			case 0x24: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'e'; break;
			case 0x2D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'r'; break;
			case 0x2C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 't'; break;
			case 0x35: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'y'; break;
			case 0x3C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'u'; break;
			case 0x43: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'i'; break;
			case 0x44: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'o'; break;
			case 0x4D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'p'; break;
			case 0x54: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '['; break;
			case 0x5B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = ']'; break;

			case 0x1C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'a'; break;
			case 0x1B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 's'; break;
			case 0x23: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'd'; break;
			case 0x2B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'f'; break;
			case 0x34: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'g'; break;
			case 0x33: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'h'; break;
			case 0x3B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'j'; break;
			case 0x42: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'k'; break;
			case 0x4B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'l'; break;
			case 0x4C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = ';'; break;
			case 0x52: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '\''; break;
			case 0x1A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'z'; break;
			case 0x22: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'x'; break;

			case 0x21: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'c'; break;
			case 0x2A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'v'; break;
			case 0x32: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'b'; break;
			case 0x31: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'n'; break;
			case 0x3A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = 'm'; break;
			case 0x41: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = ','; break;
			case 0x49: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '.'; break;
			case 0x4A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '/'; break;
			case 0x29: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = ' '; break;
			case 0x5A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '\n'; break;
		}
	
		PS2_buffer_data->cur_buf_length++;
	
		PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '\0';
	}
}

void read_PS2_data(int *make_code_flag, int *PS2_code) {
	int data;
	
	data = IORD(PS2_CONTROLLER_COMPONENT_0_BASE, 0);
	*make_code_flag = (data >> 8) & 0x1;
	*PS2_code = data & 0xFF;
}

// ISR when the a PS2 code is acquired
void handle_PS2_interrupts(PS2_buffer_struct *PS2_buffer_data)
{
	int make_code_flag, PS2_code;
	
	read_PS2_data(&make_code_flag, &PS2_code);
	
	if (make_code_flag == 1) {
		translate_PS2_code(PS2_buffer_data, PS2_code);
		PS2_buffer_data->buffer_flush = 1;		
	}
		
	IOWR(PS2_CONTROLLER_COMPONENT_0_BASE, 0, 0);
}

// Function for initializing the ISR of the PS2_controller
void init_PS2_irq(PS2_buffer_struct *PS2_buffer_data) {
	IOWR(PS2_CONTROLLER_COMPONENT_0_BASE, 0, 0);

	alt_irq_register(PS2_CONTROLLER_COMPONENT_0_IRQ, (void *)PS2_buffer_data, (void*)handle_PS2_interrupts );
}
