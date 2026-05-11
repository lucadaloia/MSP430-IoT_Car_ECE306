//******************************************************************************
//  File Name: globals.c
//  Description: This file contains the global variables.
//  Author: Luca
//  Date: Feb 2026
//******************************************************************************
#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include "macros.h"
#include  "ports.h"
#include "globals.h"

//---------------
//DAC
volatile unsigned int DAC_data;
volatile unsigned int overflow_count = 0;
volatile unsigned int DAC_Target = DAC_Adjust;

//-----------------------
// Black Line
volatile unsigned int black_line_case = 0;
volatile unsigned int bl_counter = 0;
volatile unsigned int bl_count = 0;

//------------
//PID
volatile float error_sum;
volatile float prev_error = 0;
volatile int right_offset;
volatile int left_offset;

volatile unsigned int BL_start = OFF;
volatile unsigned int BL_counter = 0;

unsigned int black_limit = 550;
unsigned int white_limit = 0;


//-------------------------------------------
//Command control
unsigned int command_active;
char command = 'V';
unsigned int command_timer;
unsigned int command_duration;
char last_command = ' ';

unsigned int Menu_Page;

volatile char ip_part1[11] = {'\0'};
volatile char ip_part2[11] = {'\0'};
volatile char ssid[11] = {'\0'};

unsigned int ThumbWheel;

char time_str[5];
char password_str[5];
char command_combined[11];
//-------------------------------------------
// Initialization Sequence
int initialization_counter = 0;
int counter50ms = 0;
int curr_counter = 0;
int BOOT_complete = 0;
int last_init_counter = -1;

volatile char IP[20];
volatile char SSID[33];

volatile unsigned int AT_state = 1;




// IoT
volatile unsigned int usb_active = 0;
volatile unsigned int one_second_passed;
volatile unsigned int transmit_done = YES;
volatile unsigned int command_state = NO;
volatile unsigned int rx_done = NO;


//UART
volatile char UCA0_RX_Ring_Buf[RING_BUFFER_SIZE];
volatile char UCA1_RX_Ring_Buf[RING_BUFFER_SIZE];
volatile char UCA0_TX_Ring_Buf[RING_BUFFER_SIZE];
volatile char UCA1_TX_Ring_Buf[RING_BUFFER_SIZE];

volatile char UCA0_Process_Buf[NUM_PROCESS_BUFS][LARGE_BUFFER_SIZE];
volatile char UCA1_Process_Buf[NUM_PROCESS_BUFS][LARGE_BUFFER_SIZE];

volatile unsigned int buf_num;
volatile unsigned int buf0_num;
volatile unsigned int buf_index;
volatile unsigned int ProcessBuf_rd;

volatile unsigned int UCA0_RX_wr = 0;
volatile unsigned int UCA0_RX_rd = 0;
volatile unsigned int UCA0_TX_rd = 0;
volatile unsigned int UCA1_RX_wr = 0;
volatile unsigned int UCA1_RX_rd = 0;
volatile unsigned int UCA1_TX_rd = 0;

volatile unsigned char baud_change = '0';


unsigned char rx_char;
volatile unsigned int startup_timer = 0; // Increments every 200ms in ISR
char transmission_state = WAITING;
unsigned int project_8_state;

volatile char current_baud = 'S';

volatile unsigned int transmit_flag = FALSE;
volatile unsigned int transmit_target;

// Project 6 - ADC
volatile char thousands;
volatile char hundreds;
volatile char tens;
volatile char ones;
volatile unsigned int ADC_Thumb_Wheel; // Holds Thumbwheel value
volatile unsigned int ADC_Left_Detect; // Holds Left IR value
volatile unsigned int ADC_Right_Detect;// Holds Right IR value
volatile unsigned int ADC_Channel;     // Tracks the state machine
char adc_char[10];
volatile unsigned int adc_counter;

volatile unsigned int IR_state = OFF;
volatile unsigned int line_detect_state;

volatile unsigned int wait_count;
// Homework 6 - Debounce
volatile unsigned int sw1_debounce_count;
volatile unsigned int sw2_debounce_count;

// Project 05
volatile unsigned int movement_state = OFF;
volatile unsigned int ms200_count;
volatile unsigned int ping_counter;
volatile unsigned int ping_state = OFF;

// Project 04 (Shapes)
volatile unsigned int Time_Sequence;
volatile unsigned int old_Time_Sequence;
volatile unsigned int Last_Time_Sequence;
volatile unsigned int cycle_time;
volatile unsigned int time_change;
volatile unsigned int what_to_do;

volatile unsigned int shape_selection = NONE;

volatile unsigned int left_wheel_on;
volatile unsigned int right_wheel_on;
volatile unsigned int segment_count;
volatile unsigned int fig_8_count;
volatile unsigned int triangle_turn_count;
volatile unsigned int triangle_turns;

volatile char state = 'W';
volatile unsigned int delay_start;

// Debounce
volatile unsigned int count_debounce_SW1;
volatile unsigned int okay_to_look_at_switch1 = OKAY;
volatile unsigned int sw1_position = RELEASED;

volatile unsigned int count_debounce_SW2;
volatile unsigned int okay_to_look_at_switch2 = OKAY;
volatile unsigned int sw2_position = RELEASED;



// Global Variables Definitions
volatile char slow_input_down;
char display_line[4][11];
char *display[4];
unsigned char display_mode;
volatile unsigned char display_changed;
volatile unsigned char update_display;
volatile unsigned int update_display_count;

volatile char one_time;
unsigned int test_value;
char chosen_direction;
char change;
unsigned int wheel_move;
char forward;
