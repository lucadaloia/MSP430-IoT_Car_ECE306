//******************************************************************************
// File Name:   interrupts.c
// Description: Primary Interrupt Service Routine (ISR) handler for Timers
//              and GPIO Ports. Manages real-time events and debouncing.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"

//---------------------------------------------------
// Switch 1 Iterrupt
#pragma vector = PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
    //switch 1
    if (P4IFG & SW1){
        P4IE &= ~SW1;   // Disable the SW1 interrupt
        P4IFG &= ~SW1;  // SW1 IFG cleared

        TB0CCR1 = TB0R + SW1_DEBOUNCE_VALUE;    //set "alarm" interrupt interval
        TB0CCTL1 |= CCIE;    //enable B0 CCR1 interrupt

        // perform SW1 action
        transmit_flag = TRUE;
        project_8_state = TRANSMIT;

    }
}

//---------------------------------------------------
// Switch 2 Iterrupt
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
    // Switch 2
    if (P2IFG & SW2) {
        P2IE &= ~SW2;   // Disable the SW2 interrupt
        P2IFG &= ~SW2; // SW2 IFG cleared

        TB0CCR2 = TB0R + SW2_DEBOUNCE_VALUE;    //set "alarm" interrupt interval
        TB0CCTL2 |= CCIE;    //enable B0 CCR2 interrupt

        // Perform SW2 Action
        if (current_baud == 'F') current_baud = "S";
        else current_baud = 'F';
        baud_change = TRUE;

    }
}

//---------------------------------------------------
//ADC Interrupt
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
        case ADCIV_NONE:
            break;
        case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
            // before its previous conversion result was read.
            break;
        case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
            break;
        case ADCIV_ADCHIIFG: // Window comparator interrupt flags
            break;
        case ADCIV_ADCLOIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCINIFG: // Window comparator interrupt flag
            break;
        case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
            ADCCTL0 &= ~ADCENC; // Disable ENC bit.
            switch (ADC_Channel++){
                case 0x00: // Channel A2 Interrupt
                    ADC_Left_Detect = (ADCMEM0) / 4; // Move result into Global Values
                    ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
                    ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
                    break;
                case 0x01: // Channel A3 Interrupt
                    ADC_Right_Detect = (ADCMEM0) / 4; // Move result into Global Values
                    ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
                    ADCMCTL0 |= ADCINCH_5; // Enable Next channel 5
                    break;
                case 0x02:
                    ADC_Thumb_Wheel = (4095 - ADCMEM0) / 4; // Move result into Global Values
                    ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A3
                    ADCMCTL0 |= ADCINCH_2; // Enable First channel 2
                    ADC_Channel=0;
                    break;
                default:
                    break;
            }
            ADCCTL0 |= ADCENC; // Enable Conversions
            ADCCTL0 |= ADCSC; // Start next sample
            break;
        default:
            break;
    }
}



//---------------------------------------------------
// Timer B0 ISRs
// CCR0 --> 200ms Interval (Display + movement)
// CCR1 --> SW1 Debounce
// CCR2 --> SW2 Debounce
// Overflow -->

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
    TB0CCR0 = TB0R + TB0CCR0_INTERVAL;        // schedule next CCR0 interrupt
    TB0CCTL0 &= ~CCIFG;                // Clear flag

    // 200ms update display
    update_display = TRUE;
    ms200_count++;
    startup_timer++;
    bl_counter++;

    adc_counter++;
    if(adc_counter > 4){
        adc_counter = 0;         // reset counter
        ADCCTL0 |= ADCSC;        // start ADC conversion

    }
    if(ms200_count++ % 5 == 0) one_second_passed = YES;
}

#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void){
    switch (__even_in_range(TB0IV, 14)) {
      case 2:  // CCR1
          sw1_debounce_count++;             // Increment your software counter
          if (sw1_debounce_count >= 8) {   // 8 * 100ms = 800ms
              P4IE |= SW1;                  // Re-enable Switch 1
              P4IFG &= ~SW1;                // Clear flag
              TB0CCTL1 &= ~CCIE;            // Stop this timer interrupt
              sw1_debounce_count = 0;       // Reset for next time


          } else {
              TB0CCR1 = TB0R + SW1_DEBOUNCE_VALUE;              // Schedule next 100ms "tick"
          }
        break;
      case 4:  // CCR2
          sw2_debounce_count++;             // Increment your software counter
          if (sw2_debounce_count >= 8) {   // 8 * 100ms = 800ms
              P2IE |= SW2;                  // Re-enable Switch 2
              P2IFG &= ~SW2;                // Clear flag
              TB0CCTL2 &= ~CCIE;            // Stop this timer interrupt
              sw2_debounce_count = 0;       // Reset for next time


          } else {
              TB0CCR2 = TB0R + SW2_DEBOUNCE_VALUE;              // Schedule next 100ms "tick"
          }

        break;
      case 14: // Overflow case
            overflow_count++;

            // 1. Wait for stability (3 overflows), then turn on power
            if (overflow_count == 1) {
                P2OUT |= DAC_ENB;         // Enable Power
                P1OUT |= RED_LED;              // Visual indicator power is on
            }

            // 2. Once power is on, begin ramping speed
            if (overflow_count > 3) {
                if (DAC_data > DAC_Target) { // Note: lower value = higher speed
                    DAC_data -= 50;         // Step the speed up
                    SAC3DAT = DAC_data;     // Update DAC output
                }
                else {
                    // 3. Target speed reached
                    DAC_data = DAC_Adjust;  // Final calibrated speed
                    SAC3DAT = DAC_data;     // Update DAC output
                    TB0CTL &= ~TBIE;        // Stop ramping interrupts
                    P1OUT &= ~RED_LED;            // Ramp complete
                }
            }
            break;

      default:
        break;
    }
}


//----------------------------------------------------------
// Timer B1 ISRs
// CCR0 --> E-Brake STOP --> DO NOT REMOVE!
// CCR1 --> 1ms --> command timer
// CCR2 --> 50ms
// Overflow -->

#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
   // line_detect_state = STOP;

    TB1CCTL0 &= ~CCIE;                        // disable interrupt
    TB1CCTL0 &= ~CCIFG;                // Clear flag

}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void Timer1_B1_ISR(void){
    switch(__even_in_range(TB1IV,14)){
      case 0: break;
      case 2:   // CCR1

          if (command_active){
              command_timer++;
              if (command_timer >= command_duration){
                  // Command done --> reset all variables for next command
                  command_active = OFF;
                  command_timer = 0;
                  command_duration = 0;
                  command = '0';
              }
          }

          TB1CCR1 = TB1R + TB1CCR1_INTERVAL;     // Schedule next interrupt (1ms later)
          TB1CCTL1 &= ~CCIFG;           // clear flag

        break;
      case 4: // CCR2
          TB1CCR2 = TB1R + TB1CCR2_INTERVAL;
          TB1CCTL2 &= ~CCIFG;                // Clear flag
          initialization_counter++;
          counter50ms++;
          ping_counter++;

          if (ping_counter >= 300){
              ping_state = YES;
              ping_counter = 0;
          }

          break;
      case 14: break; // overflow
      default: break;
    }
  }


