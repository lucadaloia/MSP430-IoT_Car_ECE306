//******************************************************************************
//  File Name: ports.h
//  Description: This file contains the function prototypes for port
//               initialization routines defined in ports.c.
//  Author: Luca
//  Date: Feb 2026
//  Compiler: Built with Code Composer Studio Version: 12.4.0.00007
//******************************************************************************

#ifndef PORTS_H_
#define PORTS_H_

//--------------------------------------------------------------
// Port #defines

// Port 1 Pin Macros
#define RED_LED           (0x01) // 0 RED_LED
#define A1_SEEED          (0x02) // 1 A1_SEEED
#define V_DETECT_L        (0x04) // 2 V_DETECT_L
#define V_DETECT_R        (0x08) // 3 V_DETECT_R
#define A4_SEEED          (0x10) // 4 A4_SEEED
#define V_THUMB           (0x20) // 5 V_THUMB
#define UCA0TXD           (0x40) // 6 UCA0TXD
#define UCA0RXD           (0x80) // 7 UCA0RXD

// Port 2 Pin Macros
#define SLOW_CLK          (0x01) // 0 SLOW_CLK
#define CHECK_BAT         (0x02) // 1 CHECK_BAT
#define IR_LED            (0x04) // 2 IR_LED
#define SW2               (0x08) // 3 SW2
#define IOT_RUN_CPU       (0x10) // 4 IOT_RUN_CPU
#define DAC_ENB           (0x20) // 5 DAC_ENB
#define LFXOUT            (0x40) // 6 LFXOUT
#define LFXIN             (0x80) // 7 LFXIN

// Port 3 Pin Macros
#define TEST_PROBE        (0x01) // 0 TEST_PROBE
#define OA2O              (0x02) // 1 OA2O
#define OA2N              (0x04) // 2 OA2N
#define OA2P              (0x08) // 3 OA2P
#define SMCLK_OUT         (0x10) // 4 SMCLK_OUT
#define DAC_CTRL_3        (0x20) // 5 DAC_CTRL_3
#define IOT_LINK_CPU      (0x40) // 6 IOT_LINK_CPU
#define IOT_RN_CPU        (0x80) // 7 IOT_RN_CPU

// Port 4 Pin Macros
#define RESET_LCD         (0x01) // 0 RESET_LCD
#define SW1               (0x02) // 1 SW1
#define UCA1RXD           (0x04) // 2 UCA1RXD
#define UCA1TXD           (0x08) // 3 UCA1TXD
#define UCB1_CS_LCD       (0x10) // 4 UCB1_CS_LCD
#define UCB1CLK           (0x20) // 5 UCB1CLK
#define UCB1SIMO          (0x40) // 6 UCB1SIMO
#define UCB1SOMI          (0x80) // 7 UCB1SOMI

// Port 5 Pin Macros
#define V_BAT             (0x01) // 0 V_BAT
#define V_5               (0x02) // 1 V_5
#define V_DAC             (0x04) // 2 V_DAC
#define V3_3              (0x08) // 3 V3_3
#define IOT_BOOT_CPU      (0x10) // 4 IOT_BOOT_CPU

// Port 6 Pin Macros
#define LCD_BACKLITE      (0x01) // 0 LCD_BACKLITE
#define L_FORWARD         (0x02) // 1 L_FORWARD
#define R_FORWARD         (0x04) // 2 R_FORWARD
#define L_REVERSE         (0x08) // 3 L_REVERSE
#define R_REVERSE         (0x10) // 4 R_REVERSE
#define P6_5              (0x20) // 5 P6_5
#define GRN_LED           (0x40) // 6 GRN_LED

//--------------------------------------------------------------

// Prototypes
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);


#endif /* PORTS_H_ */
