//******************************************************************************
// File Name:   timers.c
// Description: Timer B configuration. Manages PWM generation for motor
//              speed control and periodic interrupts for system timing.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"

void Init_Timers(void) {
    Init_Timer_B0();
    Init_Timer_B3();
}

void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK;     // SMCLK (8MHz)
    TB0CTL |= TBCLR;            // Resets TB0R
    TB0CTL |= MC__CONTINUOUS;   // Continuous Mode
    TB0CTL |= ID__8;            // Divider /8
    TB0EX0 = TBIDEX__8;         // Expansion Divider /8 (Total /64)

    TB0CCR0 = TB0CCR0_INTERVAL;            // 200ms Interval
    TB0CCTL0 |= CCIE;           // Enable CCR0 Interrupt

    TB0CTL |= TBIE;
}

void Init_Timer_B1(void) {
    TB1CTL = TBSSEL__SMCLK | TBCLR;    // Select SMCLK and clear timer
    TB1CTL |= MC__CONTINUOUS;          // Continuous mode
    TB1CTL |= TIMER_DIVIDER_MAIN;      // Divide by 2
    TB1EX0  = TIMER_DIVIDER_EXPAND;    // Divide by 8

    TB1CCR0 = TB1CCR0_INTERVAL;        // 50ms interval
    TB1CCTL0 &= ~CCIFG;                // Clear flag
    TB1CCTL0 |= CCIE;

    TB1CCR1 = TB1R + TB1CCR1_INTERVAL;;
    TB1CCTL1 &= ~CCIFG;                // Clear the interrupt flag
    TB1CCTL1 |= CCIE;                  // Enable the interrupt for CCR1

    TB1CCR2 = TB1CCR2_INTERVAL;
    TB1CCTL2 &= ~CCIFG;
}

void Init_Timer_B3(void) {
    //------------------------------------------------------------------------------
    // SMCLK source, up count mode, PWM Right Side
    // TB3.1 P6.1 L_FORWARD
    // TB3.2 P6.2 R_FORWARD
    // TB3.3 P6.3 L_REVERSE
    // TB3.4 P6.4 R_REVERSE
    // TB3.5 P6.5 LCD_BACKLITE
    //------------------------------------------------------------------------------
    TB3CTL = TBSSEL__SMCLK; // SMCLK
    TB3CTL |= MC__UP; // Up Mode
    TB3CTL |= TBCLR; // Clear TAR

    PWM_PERIOD = WHEEL_PERIOD; // PWM Period

    TB3CCTL1 = OUTMOD_7; // CCR5 reset/set
    LCD_BACKLITE_DIMING = PERCENT_OFF; // P6.5 LCD_BACKLITE On Diming percent (set to Off = 0)

    TB3CCTL2 = OUTMOD_7; // CCR1 reset/set
    LEFT_FORWARD_SPEED = PERCENT_OFF; // P6.1 Left Forward PWM duty cycle

    TB3CCTL3 = OUTMOD_7; // CCR2 reset/set
    RIGHT_FORWARD_SPEED = PERCENT_OFF; // P6.2 Right Forward PWM duty cycle

    TB3CCTL4 = OUTMOD_7; // CCR3 reset/set
    LEFT_REVERSE_SPEED = PERCENT_OFF; // P6.3 Left Reverse PWM duty cycle

    TB3CCTL5 = OUTMOD_7; // CCR4 reset/set
    RIGHT_REVERSE_SPEED = PERCENT_OFF; // P6.4 Right Reverse PWM duty cycle


    //------------------------------------------------------------------------------
}

