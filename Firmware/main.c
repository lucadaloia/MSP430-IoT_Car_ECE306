//******************************************************************************
// File Name:   main.c
// Description: Main Operating System.
//              Handles the sequential startup and main background loop.
// Author:      Luca
// Date:        April 2026
//
// LICENSE & DISCLAIMER:
// This software is provided "as-is" for portfolio demonstration purposes only.
// The author grants permission to view and learn from this code. However,
// the author assumes no liability for any misuse of this software in
// academic environments. This code is NOT intended to be used as a
// substitute for original student work.
//******************************************************************************

#include "ProjectMaster.h"

// Function Prototypes
void main(void);
void Init_Conditions(void);


void main(void){
  //---------------------------------------------------
  // Sequential Startup

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Timer_B1();
  Init_Conditions();                   // Initialize Variables and Initial Conditions


  __enable_interrupt();               // START TIME

  BOOT_complete = 0;
  int last_init_counter = -1;
  TB1CCTL2 |= CCIE;
  int i;
  int sent = 0;
  int ip_rd;
  int ssid_rd;
  while (!BOOT_complete){

      if (initialization_counter != last_init_counter) {      //Only run this block if the time has CHANGED
          last_init_counter = initialization_counter;         // Update tracker

          switch(initialization_counter){
              case 20:    // 1sec

                                // Make sure LCD Backlite is off
                  Init_LCD();                          // Initialize LCD
                  Init_ADC();                          // Initialize ADC

                  break;
              case 22:    // 1.1sec

                  // Initialize UAC/Serial
                  Init_Serial_UCA0();
                  Init_Serial_UCA1();
                  break;
              case 24:    // 1.2sec
                  P3OUT |= IOT_RN_CPU;

                  break;
              case 30:    // 1.5sec

                  Init_Timers();
                  LCD_BACKLITE_DIMING = PERCENT_OFF;
                  break;
              case 31:
                  // set IOT EN to low

                  P3OUT &= ~IOT_RN_CPU;

                  break;
              case 38:
                  // set IOT EN back HIGH
                  P3OUT |= IOT_RN_CPU;
                  break;
              case 60:
                  if (!sent){
                      UCA0_transmit("AT+SYSSTORE=0\r\n");
                      sent = 1;
                  }

                  break;
              case 69:
                  sent = 0;
                  break;
              case 70:
                  if (!sent){
                      UCA0_transmit("AT+CIPMUX=1\r\n");
                      sent = 1;
                  }
                  break;
              case 79:
                  sent = 0;
                  break;
              case 80:
                  if (!sent){
                      UCA0_transmit("AT+CIPSERVER=1,9000\r\n");
                      sent = 1;
                  }
                  break;
              case 400:
                  UCA0_RX_rd = UCA0_RX_wr;
                  UCA0_transmit("AT+CIFSR\r\n");

                  break;
              case 450:
                  ip_rd = (UCA0_RX_rd + 24) % RING_BUFFER_SIZE;
                  for (i = 0; i < RING_BUFFER_SIZE; i++){
                      if (UCA0_RX_Ring_Buf[ip_rd] == '"') break;
                      IP[i] = UCA0_RX_Ring_Buf[ip_rd];
                      ip_rd++;
                      if (ip_rd >= RING_BUFFER_SIZE) ip_rd = BEGINNING;
                  }

                  break;
              case 520:
                  UCA0_RX_rd = UCA0_RX_wr;
                  UCA0_transmit("AT+CWJAP?\r\n");
                  break;

              case 550:
                  ssid_rd = (UCA0_RX_rd + 19) % RING_BUFFER_SIZE;
                  for (i = 0; i < 10; i++){
                      if (UCA0_RX_Ring_Buf[ssid_rd] == '"') break;
                      SSID[i] = UCA0_RX_Ring_Buf[ssid_rd];
                      ssid_rd++;

                      if (ssid_rd >= RING_BUFFER_SIZE) ssid_rd = BEGINNING;
                  }
                  BOOT_complete = 1;                   // Exit Boot Sequence

                  break;
              default:
                  break;
          }
      }
  }

  //--------------------------------
  // DIsplay IP and SSID

  PM5CTL0 &= ~LOCKLPM5;



  int dot_count = 0;
  int split_id = 0;
  int j;
  for (j = 0; j < strlen(IP); j++){
      if (IP[j] == '.'){
          dot_count++;
          if (dot_count == 2){
              split_id = j;
              break;
          }
      }
  }

  strncpy(ip_part1, IP, split_id);
  strcpy(ip_part2, IP + split_id + 1);
  strncpy(ssid, SSID, 10);




  display_changed = TRUE;
  Display_Update(0,0,0,0);

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    Display_Process();                 // Update Display
    if(Time_Sequence != old_Time_Sequence){
        old_Time_Sequence = Time_Sequence;
        cycle_time++;
        time_change = 1;
    }

    if (ping_state){
        UCA0_transmit("AT+PING=\"google.com\"\r\n");
        ping_state = OFF;
    }

    display_menu();

    UCA0_Process();
    process_command();
    run_command();

    display_changed = TRUE;

  }
}





