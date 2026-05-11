//******************************************************************************
// File Name:   ports.c
// Description: GPIO Initialization. Configures Pin Muxing, internal
//              resistors, and Port Mapping for the MSP430FR2355.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"



void Init_Ports(void) {
    Init_Port1(); // call function to initialize the Port 1 pins
    Init_Port2(); // call function to initialize the Port 2 pins
    Init_Port3(); // call function to initialize the Port 3 pins
    Init_Port4(); // call function to initialize the Port 4 pins
    Init_Port5(); // call function to initialize the Port 5 pins
    Init_Port6(); // call function to initialize the Port 6 pins
}

// Configures Port 1 pins
void Init_Port1(void){ // Configure Port 1
//------------------------------------------------------------------------------
    P1OUT = 0x00; // P1 set Low
    P1DIR = 0x00; // Set P1 direction to output

    P1SEL0 &= ~RED_LED; // RED_LED GPIO operation
    P1SEL1 &= ~RED_LED; // RED_LED GPIO operation
    P1OUT &= ~RED_LED; // Initial Value = LOW
    P1DIR |= RED_LED; // Direction = OUTPUT

    P1SEL0 |= A1_SEEED; // A1_SEEED Function operation
    P1SEL1 |= A1_SEEED; // A1_SEEED Function operation

    P1SEL0 |= V_DETECT_L; // V_DETECT_L Function operation
    P1SEL1 |= V_DETECT_L; // V_DETECT_L Function operation

    P1SEL0 |= V_DETECT_R; // V_DETECT_R Function operation
    P1SEL1 |= V_DETECT_R; // V_DETECT_R Function operation

    P1SEL0 |= A4_SEEED; // A4_SEEED Function operation
    P1SEL1 |= A4_SEEED; // A4_SEEED Function operation

    P1SEL0 |= V_THUMB; // V_THUMB Function operation
    P1SEL1 |= V_THUMB; // V_THUMB Function operation

    P1SEL0 |= UCA0TXD; // UCA0TXD Function operation
    P1SEL1 &= ~UCA0TXD; // UCA0TXD Function operation

    P1SEL0 |= UCA0RXD; // UCA0RXD Function operation
    P1SEL1 &= ~UCA0RXD; // UCA0RXD Function operation
//------------------------------------------------------------------------------
}


// Configures Port 2 pins
void Init_Port2(void){ // Configure Port 2
//------------------------------------------------------------------------------
    P2OUT = 0x00; // P2 set Low
    P2DIR = 0x00; // Set P2 direction to output

    P2SEL0 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2SEL1 &= ~SLOW_CLK; // SLOW_CLK GPIO operation
    P2OUT &= ~SLOW_CLK; // Initial Value = LOW
    P2DIR |= SLOW_CLK; // Direction = OUTPUT

    P2SEL0 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2SEL1 &= ~CHECK_BAT; // CHECK_BAT GPIO operation
    P2OUT &= ~CHECK_BAT; // Initial Value = LOW
    P2DIR |= CHECK_BAT; // Direction = OUTPUT

    P2SEL0 &= ~IR_LED; // IR_LED GPIO operation
    P2SEL1 &= ~IR_LED; // IR_LED GPIO operation
    P2OUT &= ~IR_LED; // Initial Value = LOW
    P2DIR |= IR_LED; // Direction = OUTPUT

    P2SEL0 &= ~SW2; // SW2 GPIO operation
    P2SEL1 &= ~SW2; // SW2 GPIO operation
    P2OUT |= SW2; // Configure pullup resistor
    P2DIR &= ~SW2; // Direction = INPUT
    P2REN |= SW2; // Enable pullup resistor
    P2IFG &= ~SW2;// Clear any existing interrupt flag
    P2IES |=  SW2;// Set interrupt edge to Falling Edge (High-to-Low)
    P2IE  |=  SW2;// Enable the interrupt for Switch 2

    P2SEL0 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
    P2SEL1 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
    P2OUT &= ~IOT_RUN_CPU; // Initial Value = LOW
    P2DIR |= IOT_RUN_CPU; // Direction = OUTPUT

    P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
    P2OUT &= ~DAC_ENB; // Initial Value = HIGH
    P2DIR |= DAC_ENB; // Direction = OUTPUT

    P2SEL0 &= ~LFXOUT; // LFXOUT Function operation
    P2SEL1 |= LFXOUT; // LFXOUT Function operation

    P2SEL0 &= ~LFXIN; // LFXIN Function operation
    P2SEL1 |= LFXIN; // LFXIN Function operation
//------------------------------------------------------------------------------
}


// Configures Port 3 pins
void Init_Port3(void){ // Configure Port 3
//------------------------------------------------------------------------------
    P3OUT = 0x00; // P3 set Low
    P3DIR = 0x00; // Set P3 direction to input

    P3SEL0 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3SEL1 &= ~TEST_PROBE; // TEST_PROBE GPIO operation
    P3DIR &= ~TEST_PROBE; // Direction = INPUT

    P3SEL0 |= OA2O; // OA2O Function operation
    P3SEL1 |= OA2O; // OA2O Function operation

    P3SEL0 |= OA2N; // OA2N Function operation
    P3SEL1 |= OA2N; // OA2N Function operation

    P3SEL0 |= OA2P; // OA2P Function operation
    P3SEL1 |= OA2P; // OA2P Function operation

    P3SEL0 |= SMCLK_OUT; // SMCLK_OUT Function operation
    P3SEL1 |= SMCLK_OUT; // SMCLK_OUT Function operation

    P3SEL0 |= DAC_CTRL_3; // DAC_CTRL_3 GPIO operation
    P3SEL1 |= DAC_CTRL_3; // DAC_CTRL_3 GPIO operation
    P3DIR |= DAC_CTRL_3; // Direction = INPUT
    P3OUT &= ~DAC_CTRL_3;
//    P3SELC |= DAC_CTRL_3;   //DAC function

    P3SEL0 &= ~IOT_LINK_CPU; // IOT_LINK_CPU GPIO operation
    P3SEL1 &= ~IOT_LINK_CPU; // IOT_LINK_CPU GPIO operation
    P3DIR &= ~IOT_LINK_CPU; // Direction = INPUT

    P3SEL0 &= ~IOT_RN_CPU; // IOT_RN_CPU GPIO operation
    P3SEL1 &= ~IOT_RN_CPU; // IOT_RN_CPU GPIO operation
    P3DIR |= IOT_RN_CPU; // Direction = OUT
//------------------------------------------------------------------------------
}

// Configures Port 4 pins
void Init_Port4(void){ // Configure Port 4
//------------------------------------------------------------------------------
    P4OUT = 0x00; // P4 set Low
    P4DIR = 0x00; // Set P4 direction to output

    P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
    P4OUT &= ~RESET_LCD; // Initial Value = LOW
    P4DIR |= RESET_LCD; // Direction = OUTPUT

    P4SEL0 &= ~SW1; // SW1 GPIO operation
    P4SEL1 &= ~SW1; // SW1 GPIO operation
    P4OUT |= SW1; // Configure pullup resistor
    P4DIR &= ~SW1; // Direction = INPUT
    P4REN |= SW1; // Enable pullup resistor
    P4IFG &= ~SW1;// Clear any existing interrupt flag
    P4IES |=  SW1;// Set interrupt edge to Falling Edge (High-to-Low)
    P4IE  |=  SW1;// Enable the interrupt for Switch 1

    P4SEL0 |= UCA1RXD; // UCA1RXD Function operation
    P4SEL1 &= ~UCA1RXD; // UCA1RXD Function operation

    P4SEL0 |= UCA1TXD; // UCA1TXD Function operation
    P4SEL1 &= ~UCA1TXD; // UCA1TXD Function operation

    P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
    P4OUT |= UCB1_CS_LCD; // Initial Value = HIGH
    P4DIR |= UCB1_CS_LCD; // Direction = OUTPUT

    P4SEL0 |= UCB1CLK; // UCB1CLK Function operation
    P4SEL1 &= ~UCB1CLK; // UCB1CLK Function operation

    P4SEL0 |= UCB1SIMO; // UCB1SIMO Function operation
    P4SEL1 &= ~UCB1SIMO; // UCB1SIMO Function operation

    P4SEL0 |= UCB1SOMI; // UCB1SOMI Function operation
    P4SEL1 &= ~UCB1SOMI; // UCB1SOMI Function operation
//------------------------------------------------------------------------------
}

// Configures Port 5 pins
void Init_Port5(void){ // Configure Port 5
//------------------------------------------------------------------------------
    P5OUT = 0x00; // P5 set Low
    P5DIR = 0x00; // Set P5 direction to input

    P5SEL0 &= ~V_BAT; // V_BAT GPIO operation
    P5SEL1 &= ~V_BAT; // V_BAT GPIO operation
    P5DIR &= ~V_BAT; // Direction = INPUT

    P5SEL0 &= ~V_5; // V_5 GPIO operation
    P5SEL1 &= ~V_5; // V_5 GPIO operation
    P5DIR &= ~V_5; // Direction = INPUT

    P5SEL0 &= ~V_DAC; // V_DAC GPIO operation
    P5SEL1 &= ~V_DAC; // V_DAC GPIO operation
    P5DIR &= ~V_DAC; // Direction = INPUT

    P5SEL0 &= ~V3_3; // V3_3 GPIO operation
    P5SEL1 &= ~V3_3; // V3_3 GPIO operation
    P5DIR &= ~V3_3; // Direction = INPUT

    P5SEL0 &= ~IOT_BOOT_CPU; // IOT_BOOT_CPU GPIO operation
    P5SEL1 &= ~IOT_BOOT_CPU; // IOT_BOOT_CPU GPIO operation
    P5DIR &= ~IOT_BOOT_CPU; // Direction = INPUT
    P5OUT |= IOT_BOOT_CPU;
//------------------------------------------------------------------------------
}

// Configures Port 6 pins
void Init_Port6(void){ // Configure Port 6
//------------------------------------------------------------------------------
    P6OUT = 0x00; // P6 set Low
    P6DIR = 0x00; // Set P6 direction to input

    P6SEL0 |= LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    P6SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPIO operation
    P6OUT &= ~LCD_BACKLITE; // Initial Value = HIGH
    P6DIR |= LCD_BACKLITE; // Direction = OUTPUT

    P6SEL0 |= R_FORWARD; // R_FORWARD GPIO operation
    P6SEL1 &= ~R_FORWARD; // R_FORWARD GPIO operation
    P6DIR |= R_FORWARD; // Direction = OUTPUT
    P6OUT &= ~R_FORWARD; //Setting initial value to LOW


    P6SEL0 |= L_FORWARD; // L_FORWARD GPIO operation
    P6SEL1 &= ~L_FORWARD; // L_FORWARD GPIO operation
    P6DIR |= L_FORWARD; // Direction = OUTPUT
    P6OUT &= ~L_FORWARD; //Setting initial value to LOW

    P6SEL0 |= R_REVERSE; // R_REVERSE GPIO operation
    P6SEL1 &= ~R_REVERSE; // R_REVERSE GPIO operation
    P6DIR |= R_REVERSE; // Direction = output
    P6OUT &= ~R_REVERSE; //Setting initial value to LOW

    P6SEL0 |= L_REVERSE; // L_REVERSE GPIO operation
    P6SEL1 &= ~L_REVERSE; // L_REVERSE GPIO operation
    P6DIR |= L_REVERSE; // Direction = output
    P6OUT &= ~L_REVERSE; //Setting initial value to LOW

    P6SEL0 &= ~P6_5; // P6_5 GPIO operation
    P6SEL1 &= ~P6_5; // P6_5 GPIO operation
    P6DIR &= ~P6_5; // Direction = INPUT

    P6SEL0 &= ~GRN_LED; // GRN_LED GPIO operation
    P6SEL1 &= ~GRN_LED; // GRN_LED GPIO operation
    P6OUT &= ~GRN_LED; // Initial Value = LOW
    P6DIR |= GRN_LED; // Direction = OUTPUT
//------------------------------------------------------------------------------
}


