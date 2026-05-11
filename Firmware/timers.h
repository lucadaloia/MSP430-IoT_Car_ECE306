/*
 * timers.h
 *
 *  Created on: Mar 3, 2026
 *      Author: Luca
 */

#ifndef TIMERS_H_
#define TIMERS_H_

void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B3(void);

// PWM
#define PWM_PERIOD (TB3CCR0)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define RIGHT_FORWARD_SPEED (TB3CCR3)
#define LEFT_REVERSE_SPEED (TB3CCR4)
#define RIGHT_REVERSE_SPEED (TB3CCR5)
#define LCD_BACKLITE_DIMING (TB3CCR1)

#define WHEEL_PERIOD        (50005)

// --- Timer Divider Setup ---
#define TIMER_DIVIDER_MAIN     (ID__2)      // Divide by 2
#define TIMER_DIVIDER_EXPAND   (TBIDEX__8)  // Divide by 8

// 10ms interval = 10ms / (2s) = 5,000 ticks
#define TB0CCR0_INTERVAL       (100000)   // 200ms
#define TB1CCR0_INTERVAL        (25000) //50ms
#define TB1CCR1_INTERVAL           (5000) //10ms
#define TB1CCR2_INTERVAL        (25000) // 50ms

#define DEBOUNCE_INTERVAL       (5000)  //10ms




#endif /* TIMERS_H_ */
