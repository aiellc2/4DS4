// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Digital Systems Design course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef	  __define_H__
#define	  __define_H__

#include <io.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "system.h"
#include "sys/alt_irq.h"

#define MAX_STRING_LENGTH 10

typedef struct PS2_buffer {
	char string_buffer[MAX_STRING_LENGTH];
	int cur_buf_length;
	int buffer_flush;
} PS2_buffer_struct;

#include "PS2_controller.h"
	
#endif
