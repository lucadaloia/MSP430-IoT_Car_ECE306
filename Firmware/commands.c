//******************************************************************************
// File Name:   commands.c
// Description: Serial Command Parser. Decodes incoming IoT packets into
//              executable robot actions and system state changes.
// Author:      Luca
//******************************************************************************
#include "ProjectMaster.h"

void process_command(void){
    if (ProcessBuf_rd != buf0_num){
        // get the Command Chars for checking
        char *start_ptr = strchr(UCA0_Process_Buf[ProcessBuf_rd], '^');
        memset(command_combined, 0, sizeof(command_combined));
        if (start_ptr != NULL){
            char command_indicator = *start_ptr;   // get first char of buffer

            char command_id = *(start_ptr + 5);

            // Get Time


            memcpy(password_str, start_ptr + 1, 4);
            password_str[4] = '\0';
            int poassword_int = atoi(password_str);
            memcpy(time_str, start_ptr + 6, 4);
            time_str[4] = '\0';
            sprintf(command_combined, "%c%s", command_id, time_str);
            int time_int = atoi(time_str) / 10;


//            sprintf(command_combined, "%c%s", command_id, time_str);
            int current_len = strlen(command_combined);
            int i;

            // Fill with spaces starting from where the original string ended
            for (i = current_len; i < 10; i++) {
                command_combined[i] = ' ';
            }

            // CRITICAL: Manually place the null terminator at the new end of the string
            command_combined[10] = '\0';


            // process commandn if valid password
            if ((poassword_int == 2004) && (command_indicator == '^')){
                command_duration = time_int;
                command = command_id;

                //call "run_command" function

           }
        }
       ProcessBuf_rd++;
       if (ProcessBuf_rd >= NUM_PROCESS_BUFS) ProcessBuf_rd = BEGINNING;
    }
}

void run_command(void){
    //if (!command_active) command = '0';
    switch (command){
        // IDLE/OFF case
        case '0':
            stop_all();
            P2OUT &= ~DAC_ENB;  // Kill power to motors immediately
            TB0CTL &= ~TBIE;    // Stop any active ramping
            break;
        case 'V':
            stop_all();
            P2OUT &= ~DAC_ENB;  // Kill power to motors immediately
            TB0CTL &= ~TBIE;    // Stop any active ramping
            break;
        // Move Forward
        case 'F':
            command_active = ON;// sets variable to ON to alert interrupt that command is active so it can start the timer
            LCD_BACKLITE_DIMING = PERCENT_50;

            move_forward();
            break;
        // Move Backwards
        case 'B':
            command_active = ON; // sets variable to ON to alert interrupt that command is active so it can start the timer
            LCD_BACKLITE_DIMING = PERCENT_50;
            move_reverse();
            break;
        // Turn right
        case 'R':
            command_active = ON; // sets variable to ON to alert interrupt that command is active so it can start the timer
            LCD_BACKLITE_DIMING = PERCENT_50;
            spin_right();
            break;
        // Turn left
        case 'L':
            command_active = ON;    // sets variable to ON to alert interrupt that command is active so it can start the timer
            LCD_BACKLITE_DIMING = PERCENT_50;
            spin_left();
            break;

        // Command that will be sent at pad 8 to move car and begin black line routine
        case 'J':

            switch(black_line_case){
                case BL_START:
                    bl_count = 0;
                    black_line_case = HALF_CIRCLE;
                    break;
                case HALF_CIRCLE:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    if (bl_count++ < 15000){
                        RIGHT_FORWARD_SPEED = PERCENT_40;
                        LEFT_FORWARD_SPEED = PERCENT_30;
                    }
                    else {
                        stop_all();
                        LCD_BACKLITE_DIMING = 0;

                        black_line_case = BL_STOP_1;
                        bl_count = 0;
                    }
                    // Do the J shaped turn to reach the white pad
                    break;
                case BL_STOP_1:
                    P2OUT |= IR_LED;
                    stop_all();
                    if (bl_count++ > 15000){
//                        bl_count = 0;
                        black_line_case = BL_SEARCH;
                        BL_start = ON;
                    }
                    //stop for a few seconds
                    break;
                case BL_SEARCH:

                    LCD_BACKLITE_DIMING = PERCENT_50;
                    move_forward();
                    if ((ADC_Left_Detect > black_limit) && (ADC_Right_Detect > black_limit)){
                        stop_all();
                        black_line_case = BL_STOP_2;
                        bl_count = 0;
                    }
                    //look for black line
                    break;
                case BL_STOP_2:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    if (bl_count++ > 15000){
//                        bl_count = 0;
                        black_line_case = BL_TURN;
                        BL_start = ON;
                    }
                    //stop for 10 sec
                    break;
                case BL_TURN:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    spin_right();
                    if (ADC_Left_Detect > black_limit){
                        stop_all();
                        bl_counter = 0;
                        black_line_case = BL_STOP_3;
                    }
                    //turn until aligned
                    break;
                case BL_STOP_3:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    if (bl_count++ > 20000){
//                        bl_count = 0;
                        black_line_case = BL_FOLLOW;
                        BL_start = ON;
                        bl_count = 0;
                    }
                    //stop for 10 sec
                    break;
                case BL_FOLLOW:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    Black_Line();
                    if (bl_counter > 700){
                        bl_counter = 0;
                        black_line_case = BL_CIRCLE;
                    }
                    //begin following black line;
                    break;
                case BL_CIRCLE:
                    LCD_BACKLITE_DIMING = PERCENT_50;
                    Black_Line();
                    //display circle
                    break;
                default: break;
            }
            break;
        case 'H':
            stop_all();
            LCD_BACKLITE_DIMING = PERCENT_50;
            strcpy(display_line[0], "BL EXIT   ");
            center_text(display_line[1], ip_part1);
            center_text(display_line[2], ip_part2);
            strcpy(display_line[3], "          ");
            bl_count = 0;
            command = 'G';
            break;
        case 'G':
            move_forward();
            if (bl_count++ > 30000){
                stop_all();
                command = 'K';
            }
            break;
        case 'K':
            stop_all();
            strcpy(display_line[0], "BL STOP   ");
            center_text(display_line[1], ip_part1);
            center_text(display_line[2], ip_part2);
            strcpy(display_line[3], "          ");
            break;

        default: break;
    }
}


