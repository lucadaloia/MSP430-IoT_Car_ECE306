//******************************************************************************
// File Name:   menus.c
// Description: LCD Menu System. Manages display states and UI navigation
//              based on user input via the thumbwheel.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"

void display_menu(void){
    HEXtoBCD(ADC_Thumb_Wheel);
    ThumbWheel = atoi(adc_char);

    if (ThumbWheel <= NETWORK_MENU) Menu_Page = NETWORK;
    else if (ThumbWheel <= COMMANDS_MENU) Menu_Page = COMMANDS;
    else if (ThumbWheel <= CALIBRATION_MENU) Menu_Page = CALIBRATION;

    switch (Menu_Page){
    case NETWORK:
        // Display onto LCD
        center_text(display_line[0], ssid);
        center_text(display_line[1], "IP address");
        center_text(display_line[2], ip_part1);
        center_text(display_line[3], ip_part2);
        break;
    case COMMANDS:
        switch (command){
            // IDLE/OFF case
            case '0':
                lcd_4line();
                strcpy(display_line[0], "          ");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                strcpy(display_line[3], "          ");
//                strcpy(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_OFF;
                break;
            case 'V':
                lcd_4line();
                strcpy(display_line[0], "  Waiting ");
                strcpy(display_line[1], "for input ");
                center_text(display_line[2], ip_part1);
                center_text(display_line[3], ip_part2);
                LCD_BACKLITE_DIMING = PERCENT_OFF;
                break;
                break;

            // Move Forward
            case 'F':
                strcpy(display_line[0], " FORWARD  ");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;

                break;

            // Move Backwards
            case 'B':
                strcpy(display_line[0], " REVERSE  ");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                break;

            // Turn right
            case 'R':
                strcpy(display_line[0], "TURN RIGHT");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                break;

            // Turn left
            case 'L':
                strcpy(display_line[0], "TURN  LEFT");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                break;

            //Arrived at commands
            case '1':
                P1OUT |= RED_LED;
                strcpy(display_line[0], "Arrived 01");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '2':
                strcpy(display_line[0], "Arrived 02");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '3':
                strcpy(display_line[0], "Arrived 03");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '4':
                strcpy(display_line[0], "Arrived 04");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '5':
                strcpy(display_line[0], "Arrived 05");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '6':
                strcpy(display_line[0], "Arrived 06");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '7':
                strcpy(display_line[0], "Arrived 07");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case '8':
                strcpy(display_line[0], "Arrived 08");
                center_text(display_line[1], ip_part1);
                center_text(display_line[2], ip_part2);
                center_text(display_line[3], command_combined);
                LCD_BACKLITE_DIMING = PERCENT_50;
                break;
            case 'J':
                switch (black_line_case){
                    case HALF_CIRCLE:
                        strcpy(display_line[0], "BL START  ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        // Display "BL Start"
                        break;
                    case BL_STOP_1:
                        strcpy(display_line[0], "BL START  ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //stop for a few seconds
                        break;
                    case BL_SEARCH:
                        strcpy(display_line[0], "BL START  ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Start"
                        break;
                    case BL_STOP_2:
                        strcpy(display_line[0], "BLINTERCEPT");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Intercept"
                        break;
                    case BL_TURN:
                        strcpy(display_line[0], "BL TURN   ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Turn"
                        break;
                    case BL_STOP_3:
                        strcpy(display_line[0], "BL ALIGNED");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Aligned"
                        break;
                    case BL_FOLLOW:
                        strcpy(display_line[0], "BL TRAVEL ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Travel"
                        break;
                    case BL_CIRCLE:
                        strcpy(display_line[0], "BL CIRCLE ");
                        center_text(display_line[1], ip_part1);
                        center_text(display_line[2], ip_part2);
                        strcpy(display_line[3], "          ");
                        //Display "BL Circle"
                        break;
                    default: break;
                }
                break;
                    case CALIBRATION:
                        // --- RIGHT ---
                        strcpy(display_line[0], "          ");
                        strcpy(display_line[1], "RIGHT:    ");
                        HEXtoBCD(ADC_Right_Detect);
                        adc_line(2, 6);
                        strcpy(display_line[3], "          ");

                        // --- LEFT ---
                        strcpy(display_line[2], "LEFT:     ");
                        HEXtoBCD(ADC_Left_Detect);
                        adc_line(3, 6);
                        break;
            default: break;
        }
    }
}


