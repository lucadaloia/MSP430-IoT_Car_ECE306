//******************************************************************************
//  File Name: macros.h
//  Description: This file contains all the macro definitions used across the
//               project to eliminate magic numbers and provide descriptive
//               names for hardware pins and constant values.
//  Author: Luca
//  Date: Feb 2026
//  Compiler: Built with Code Composer Studio Version: 12.4.0.00007
//******************************************************************************

#ifndef MACROS_H_
#define MACROS_H_

//--------------------------
// Commands
#define IDLE     (0)
#define FORWARD  (1)
#define REVERSE  (2)
#define RIGHT    (3)
#define LEFT     (4)

#define YES (1)
#define NO  (0)

#define NETWORK_MENU        (342)
#define COMMANDS_MENU       (683)
#define CALIBRATION_MENU    (1024)


#define NETWORK     (0)
#define COMMANDS    (1)
#define CALIBRATION (2)

//--------------------------
// Buffers
#define RING_BUFFER_SIZE (64)
#define LARGE_BUFFER_SIZE   (64)
#define NUM_PROCESS_BUFS    (4)
#define BEGINNING   (0)

#define WAITING  (0)
#define RECEIVED (1)
#define TRANSMIT (2)

#define TRUE    (1)
#define FALSE   (0)
//--------------------------
// Timers
#define TB0CCR0_INTERVAL    (25000) //200msec
#define SW1_DEBOUNCE_VALUE  (12500) //100ms
#define SW2_DEBOUNCE_VALUE  (12500) //100ms

//--------------------------
//Project 06
#define ON                   (1)

#define OFF                  (0)
#define WAIT                 (1)
#define SEARCHING            (2)
#define FOUND                (3)
#define TURN                 (4)
#define ALIGNED              (5)

//----------
//BL
#define BL_START     0
#define HALF_CIRCLE  1
#define BL_STOP_1    2
#define BL_SEARCH    3
#define BL_STOP_2    4
#define BL_TURN      5
#define BL_STOP_3    6
#define BL_FOLLOW    7
#define BL_CIRCLE    8

//----------------
// DAC
#define DAC_Begin (2725) // 2v
#define DAC_Limit (1300) // 6.08v
#define DAC_Adjust (1350) // 6.0v
#define DAC_step    (100)

//--------------
// PWM
#define PERCENT_100 (50000)
#define PERCENT_90  (45000)
#define PERCENT_80  (40000)
#define PERCENT_70  (35000)
#define PERCENT_65  (32500)
#define PERCENT_60  (30000)
#define PERCENT_50  (25000)
#define PERCENT_40  (20000)
#define PERCENT_20  (10000)
#define PERCENT_30  (15000)
#define PERCENT_OFF     (0)

//---------------------------
// Project 04 (Shapes)
#define NONE (0)
//#define STRAIGHT ('L')
#define CIRCLE (1)
#define FIGURE_8    (3)
#define TRIANGLE    (2)

#define START ('S')
#define RUN ('R')
#define END ('E')

#define WHEEL_COUNT_TIME (10)
#define RIGHT_COUNT_TIME (7)
#define LEFT_COUNT_TIME (8)
#define TRAVEL_DISTANCE (2)
#define WAITING2START (50)
#define WHEEL_COUNT             (25)

#define LEFT_WHEEL_COUNT (18)
#define RIGHT_WHEEL_COUNT (20)

#define LEFT_WHEEL_COUNT_CIRCLE (5)
#define RIGHT_WHEEL_COUNT_CIRCLE (25)

#define LEFT_WHEEL_COUNT_8 (5)
#define RIGHT_WHEEL_COUNT_8 (35)
#define LEFT_WHEEL_COUNT_8_L (35)
#define RIGHT_WHEEL_COUNT_8_L (5)
#define TRIANGLE_STRAIGHT_COUNT  (1)
#define TRIANGLE_TURN_COUNT     (1)
#define TURN_COUNT              (180)

#define COMPLETE_TRIANGLE        (5)
#define COMPLETE_EIGHT          (50)
#define COMPLETE_CIRCLE         (45)
#define COMPLETE_STRAIGHT       (10)
#define WAIT_TIME               (500)

// Debounce
#define PRESSED            (0)
#define RELEASED           (1)
#define OKAY               (1)
#define NOT_OKAY           (0)
#define DEBOUNCE_TIME      (40000) // Adjust based on your clock speed
#define DEBOUNCE_RESTART   (0)

//-------------------------

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define TRUE                 (0x01) //

#endif /* MACROS_H_ */
