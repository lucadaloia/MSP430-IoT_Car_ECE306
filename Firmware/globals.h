//******************************************************************************
//  File Name: globals.h
//  Description: This file contains external declarations for all global
//               variables to allow cross-file access.
//  Author: Luca
//  Date: Feb 2026
//  Compiler: Built with Code Composer Studio Version: 12.4.0.00007
//******************************************************************************

#ifndef GLOBALS_H
#define GLOBALS_H
#include "ProjectMaster.h"

//-----------
// black line
extern volatile unsigned int black_line_case;
extern volatile unsigned int bl_counter;
extern volatile unsigned int bl_count;
//------------
//PID
extern volatile float error_sum;
extern volatile float prev_error;
extern volatile int right_offset;
extern volatile int left_offset;

extern volatile unsigned int BL_start;
extern volatile unsigned int BL_counter;

extern unsigned int black_limit;
extern unsigned int white_limit;

//---------------
//DAC
extern volatile unsigned int DAC_data;
extern volatile unsigned int overflow_count;
extern volatile unsigned int DAC_Target;
//-------------------------------------------
//Command control
extern unsigned int command_active;
extern unsigned int command_timer;
extern unsigned int command_duration;
extern char command;
extern char last_command;

extern unsigned int Menu_Page;

extern volatile char ip_part1[11];
extern volatile char ip_part2[11];
extern volatile char ssid[11];

extern unsigned int ThumbWheel;

extern char time_str[5];
extern char password_str[5];
extern char command_combined[11];

//-------------------------------------------
// Initialization Sequence
extern int initialization_counter;
extern int BOOT_complete;
extern volatile unsigned int tx_status;
extern volatile unsigned int pc_received;
extern volatile unsigned int iot_ring;
extern int counter50ms;
extern int curr_counter;

extern volatile char IP[20];
extern volatile char SSID[33];
extern volatile unsigned int AT_state;


// IoT
extern volatile unsigned int usb_active;
extern volatile unsigned int one_second_passed;
extern volatile unsigned int transmit_done;
extern volatile unsigned int command_state;
extern volatile unsigned int rx_done;

//Homework 08 - UART
extern volatile char UCA0_RX_Ring_Buf[RING_BUFFER_SIZE];
extern volatile char UCA1_RX_Ring_Buf[RING_BUFFER_SIZE];
extern volatile char UCA0_TX_Ring_Buf[RING_BUFFER_SIZE];
extern volatile char UCA1_TX_Ring_Buf[RING_BUFFER_SIZE];

extern volatile char UCA0_Process_Buf[NUM_PROCESS_BUFS][LARGE_BUFFER_SIZE];
extern volatile char UCA1_Process_Buf[NUM_PROCESS_BUFS][LARGE_BUFFER_SIZE];

extern volatile unsigned int buf_num;
extern volatile unsigned int buf0_num;
extern volatile unsigned int buf_index;

extern volatile unsigned int UCA0_RX_wr;
extern volatile unsigned int UCA0_RX_rd;
extern volatile unsigned int UCA0_TX_rd;
extern volatile unsigned int UCA1_RX_wr;
extern volatile unsigned int UCA1_RX_rd;
extern volatile unsigned int UCA1_TX_rd;

extern volatile unsigned char baud_change;
extern volatile char current_baud;
extern unsigned char rx_char;
extern volatile unsigned int ProcessBuf_rd;

extern volatile unsigned int startup_timer; // Increments every 200ms in ISR
extern char transmission_state;
extern unsigned int project_8_state;

extern volatile unsigned int transmit_flag;
extern volatile unsigned int transmit_target;

// Project 6 - ADC
extern volatile char thousands;
extern volatile char hundreds;
extern volatile char tens;
extern volatile char ones;
extern volatile unsigned int ADC_Thumb_Wheel;
extern volatile unsigned int ADC_Left_Detect;
extern volatile unsigned int ADC_Right_Detect;
extern volatile unsigned int ADC_Channel;
extern char adc_char[10];
extern volatile unsigned int adc_counter;

extern volatile unsigned int IR_state;
extern volatile unsigned int line_detect_state;
extern volatile unsigned int wait_count;

// Homework 6 - Debounce
extern volatile unsigned int sw1_debounce_count;
extern volatile unsigned int sw2_debounce_count;


// Project 05
extern volatile unsigned int movement_state;
extern volatile unsigned int ms200_count;
extern volatile unsigned int ping_counter;
extern volatile unsigned int ping_state;

// Project 04 (Shapes)
extern volatile unsigned int Time_Sequence;
extern volatile unsigned int Last_Time_Sequence;
extern volatile unsigned int old_Time_Sequence;
extern volatile unsigned int cycle_time;
extern volatile unsigned int time_change;
extern volatile unsigned int what_to_do;

extern volatile unsigned int shape_selection;

extern volatile unsigned int left_wheel_on;
extern volatile unsigned int right_wheel_on;
extern volatile unsigned int segment_count;
extern volatile unsigned int fig_8_count;
extern volatile unsigned int triangle_turn_count;
extern volatile unsigned int triangle_turns;

extern volatile char state;
extern volatile unsigned int delay_start;

// Debounce
extern volatile unsigned int count_debounce_SW1;
extern volatile unsigned int okay_to_look_at_switch1;
extern volatile unsigned int sw1_position;

extern volatile unsigned int count_debounce_SW2;
extern volatile unsigned int okay_to_look_at_switch2;
extern volatile unsigned int sw2_position;


// External Global Variable Declarations
extern volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

extern volatile char one_time;
extern unsigned int test_value;
extern char chosen_direction;
extern char change;
extern unsigned int wheel_move;
extern char forward;
#endif /* GLOBALS_H_ */
