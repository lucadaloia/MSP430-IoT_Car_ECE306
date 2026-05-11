//******************************************************************************
// File Name:   movement.c
// Description: Motion control module. Implements PID control algorithms
//              for line following and basic directional primitives.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"


// This function stops all movement to guarantee that Forward and Reverse are never on at the same time
void stop_all(void){
    RIGHT_FORWARD_SPEED = PERCENT_OFF;
    LEFT_FORWARD_SPEED = PERCENT_OFF;
    RIGHT_REVERSE_SPEED = PERCENT_OFF;
    LEFT_REVERSE_SPEED = PERCENT_OFF;
}

// function to move forward
void move_forward(void){
    stop_all(); // stop all movement before moving wheels again
    RIGHT_FORWARD_SPEED = PERCENT_80;
    LEFT_FORWARD_SPEED = PERCENT_60;
}

// function to move backwards
void move_reverse(void){
    stop_all(); // stop all movement before moving wheels again
    RIGHT_REVERSE_SPEED = PERCENT_80;
    LEFT_REVERSE_SPEED = PERCENT_60;
}

// function to spin right
void spin_right(void){
    stop_all(); // stop all movement before moving wheels again
    LEFT_FORWARD_SPEED = PERCENT_40;
    RIGHT_REVERSE_SPEED = PERCENT_50;
}

// function to spin left
void spin_left(void){
    stop_all(); // stop all movement before moving wheels again
    RIGHT_FORWARD_SPEED = PERCENT_50;
    LEFT_REVERSE_SPEED = PERCENT_40;
}






//PID
long u(void){
    LCD_BACKLITE_DIMING = PERCENT_50;
    int Right_Reading = ADC_Right_Detect;
    int Left_Reading = ADC_Left_Detect;
    //Constants
    // for 60% --> Kd = 420 and Kp = 70
    float Kp = 70.0;
    float Ki = 0.0;
    float Kd = 600.0;
    float offset = 0;

    //errors
    int error = Right_Reading - Left_Reading - offset;
//    error_sum += error;


    //PID
    float P = Kp * error;
//    float I = Ki * (error_sum);
    float D = Kd * (error - prev_error);

    int value = P + D;

    prev_error = error;

    return value;
}

// Update motor speeds based on PID correction
void update_motors(int correction){
    long left_speed  = PERCENT_60 + correction; // positive correction --> turn left --> decrease left speed
    long right_speed = PERCENT_60 - correction; // negative correction --> turn right --> increase right speed

    if (left_speed > PERCENT_100)  left_speed = PERCENT_100; // Check if left speed exceeds 100%
    if (right_speed > PERCENT_100) right_speed = PERCENT_100; // Check if right speed exceeds 100%

    if (left_speed < 0)  left_speed = PERCENT_OFF; // Check if left speed is negative
    if (right_speed < 0) right_speed = PERCENT_OFF; // Check if right speed is negative

    LEFT_FORWARD_SPEED  = left_speed; // Set left motor speed
    RIGHT_FORWARD_SPEED = right_speed; // Set right motor speed
}

void Black_Line(void){
    long correction = u();

    // If both sensors see white (Overshot the circle)
    if (ADC_Left_Detect < black_limit && ADC_Right_Detect < black_limit) {
        stop_all();
        LEFT_REVERSE_SPEED = PERCENT_20;
        RIGHT_REVERSE_SPEED = PERCENT_20;
    }
    else {
        // Normal PID operation
        stop_all();
        update_motors(correction);
    }
}


