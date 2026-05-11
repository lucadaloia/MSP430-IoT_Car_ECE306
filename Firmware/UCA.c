//******************************************************************************
// File Name:   UCA.c
// Description: Universal Communication Interface (eUSCI_A). Handles
//              asynchronous serial communication and ring buffer interrupts.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"

//------------------------------------------------------------------------------
// TX error (%) RX error (%)
// BRCLK      Baudrate    UCOS16    UCBRx       UCFx    UCSx    neg     pos     neg     pos
// 8000000    4800        1         104         2       0xD6    -0.08   0.04    -0.10   0.14
// 8000000    9600        1         52          1       0x49    -0.08   0.04    -0.10   0.14
// 8000000    19200       1         26          0       0xB6    -0.08   0.16    -0.28   0.20
// 8000000    57600       1         8           10      0xF7    -0.32   0.32    -1.00   0.36
// 8000000    115200      1         4           5       0x55    -0.80   0.64    -1.12   1.76
// 8000000    460800      0         17          0       0x4A    -2.72   2.56    -3.76   7.28
//------------------------------------------------------------------------------

void Init_Serial_UCA0(void){

    UCA0CTLW0 = 0;
    UCA0CTLW0 |= UCSWRST;            // Hold eUSCI_A0 in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;     // Use SMCLK as baud clock
    UCA0CTLW0 &= ~UCMSB;            // LSB first
    UCA0CTLW0 &= ~UCSPB;            // 1 stop bit
    UCA0CTLW0 &= ~UCPEN;            // No parity
    UCA0CTLW0 &= ~UCSYNC;           // UART mode
    UCA0CTLW0 &= ~UC7BIT;           // 8-bit data
    UCA0CTLW0 |= UCMODE_0;          // Standard UART

    // Set up Baud
    UCA0BRW = 4;   // Initialize for 115,200 Baud
    UCA0MCTLW = 0x5551;

    //Release from reset
    UCA0CTLW0 &= ~UCSWRST;

    //Prime the pump
//    UCA0TXBUF = 0x00;

    //En RX Interrupt
    UCA0IE |= UCRXIE;

}


void Init_Serial_UCA1(void){

    UCA1CTLW0 = 0;
    UCA1CTLW0 |= UCSWRST; // Put eUSCI in reset to configure safely
    UCA1CTLW0 |= UCSSEL__SMCLK;   // SMCLK as BRCLK (8MHz)
    UCA1CTLW0 &= ~UCMSB;          // LSB first
    UCA1CTLW0 &= ~UCSPB;          // 1 stop bit
    UCA1CTLW0 &= ~UCPEN;          // No parity
    UCA1CTLW0 &= ~UCSYNC;         // UART mode
    UCA1CTLW0 &= ~UC7BIT;         // 8-bit data
    UCA1CTLW0 |= UCMODE_0;        // Normal UART mode

    // Settings for 115,200 baud
    UCA1BRW = 4;
    UCA1MCTLW = 0x5551;

    // Release from reset
    UCA1CTLW0 &= ~UCSWRST;

    //Prime Pump
//    UCA1TXBUF = 0x00;

    //En RX Interrupt
    UCA1IE |= UCRXIE;

    usb_active = OFF;
}


void Change_UCA_Baud(char speed){
    // Put eUSCI in reset to configure safely
    UCA0CTLW0 |= UCSWRST;
    UCA1CTLW0 |= UCSWRST;



    //High Speed = 115,200 Baud
    if (speed == 'F'){
        current_baud = speed;
        // Configure UCA0
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;


        // Configure UCA1
        UCA1BRW = 4;
        UCA1MCTLW = 0x5551;


    }

    // Slow Speed = 9600 Baud
    if (speed == 'S'){
        current_baud = speed;
        // Configure UCA0
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;

        // Configure UCA1
        UCA1BRW = 52;
        UCA1MCTLW = 0x4911;
    }
    //display_changed = TRUE;
    //Release eUSCI from reset
    UCA0CTLW0 &= ~UCSWRST;
    UCA1CTLW0 &= ~UCSWRST;

    //Enable Interrupts
    UCA0IE |= UCRXIE;
    UCA1IE |= UCRXIE;

    // Clear flags
    UCA0IFG &= ~UCRXIFG;
    UCA1IFG &= ~UCRXIFG;

    //transmit_flag = TRUE;
    //transmit_target = ms200_count + 10; // for 2 secongs (200ms *10)

}

void UCA0_baud(char baud_speed){
    UCA0CTLW0 |= UCSWRST;
    if (baud_speed == 'F'){
        // Set UCA0 to 115200 baud
        UCA0BRW = 4;
        UCA0MCTLW = 0x5551;
    }
    else if (baud_speed == 'S'){
        // Set UCA0 to 9600 baud
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;
    }
    UCA0CTLW0 &= ~UCSWRST;
    //Enable Interrupts
    UCA0IE |= UCRXIE;

    // Clear flags
    UCA0IFG &= ~UCRXIFG;
}

void UCA1_transmit(char* string){


    int size = strlen(string);
    int i;

    for (i = 0; i < size; i++){
        UCA1_TX_Ring_Buf[i] = string[i];
    }
    UCA1_TX_Ring_Buf[size] = '\0';


    //strcpy(UCA1_TX_Ring_Buf, string); // strcpy the desired string into the TX_Buffer
    //UCA1_TX_Ring_Buf[10] = '\0';  // Set the 11th char to be Null --> 10 chars in LCD so we make sure the 11th is null (to be able to disable TX Interrupt)

    UCA1TXBUF = UCA1_TX_Ring_Buf[BEGINNING];
    UCA1_TX_rd = BEGINNING + 1;  // make sure it always begins from 0

    UCA1IE |= UCTXIE;   // Enable Interrupt
}

void UCA0_transmit(char* string){
    int size = strlen(string);
    int i;

    for (i = 0; i < size; i++){
        UCA0_TX_Ring_Buf[i] = string[i];
    }
    UCA0_TX_Ring_Buf[size] = '\0';

    UCA0TXBUF = UCA0_TX_Ring_Buf[BEGINNING];
    UCA0_TX_rd = BEGINNING + 1;  // make sure it always begins from 0

    UCA0IE |= UCTXIE;   // Enable Interrupt
}


void UCA1_Process(void){
    // buf_index and buf_num being used for UCA0_Process
    // check for new character
    while (UCA1_RX_wr != UCA1_RX_rd){
        char new_char = UCA1_RX_Ring_Buf[UCA1_RX_rd]; // add new character into temp variable
        UCA1_RX_Ring_Buf[UCA1_RX_rd] = '\0';
        UCA1_RX_rd++;   //increment rd
        if (UCA1_RX_rd >= LARGE_BUFFER_SIZE) UCA1_RX_rd = BEGINNING; //check for wrap around

        if (new_char == '^') {
            command_state = ON;

        }


        // check if character is end of message
        if (command_state) {
            if (new_char == '\r') {

                UCA1_Process_Buf[buf_num][buf_index] = '\0'; // insert null char into process buffer if message over
                // move to next buf
                buf_num++;
                buf_index = BEGINNING;
                rx_done = NO;
                command_state = OFF;

            }
            else {
                UCA1_Process_Buf[buf_num][buf_index] = new_char;
                buf_index++;    // increment buf_index
                // check for wrap arounds
                if (buf_index >= LARGE_BUFFER_SIZE){
                    buf_index = BEGINNING;
                    buf_num++;
                }
            }


        }


        // check for buff_num wrap around
        if (buf_num >= NUM_PROCESS_BUFS) buf_num = BEGINNING;
    }
}

void UCA0_Process(void){
    // check for new character
    while (UCA0_RX_wr != UCA0_RX_rd){
        char new_char = UCA0_RX_Ring_Buf[UCA0_RX_rd]; // add new character into temp variable
//        UCA0_RX_Ring_Buf[UCA0_RX_rd] = '\0';
        UCA0_RX_rd++;   //increment rd
        if (UCA0_RX_rd >= LARGE_BUFFER_SIZE) UCA0_RX_rd = BEGINNING; //check for wrap around

        if (new_char == '^') {
            command_state = ON;
        }

        if (command_state) {
            // check if character is end of message
            if (new_char == '\r'){

                UCA0_Process_Buf[buf0_num][buf_index] = '\0'; // insert null char into process buffer if message over
                // move to next buf
                buf0_num++;
                buf_index = BEGINNING;
                rx_done = NO;
                command_state = OFF;
            }

            else {
                UCA0_Process_Buf[buf0_num][buf_index] = new_char;    // Add new char into process buffer
                buf_index++;    // increment buf_index
                // check for wrap arounds
                if (buf_index >= LARGE_BUFFER_SIZE){
                    buf_index = BEGINNING;
                    buf0_num++;
                }
            }
        }

        // check for buff_num wrap around
        if (buf0_num >= NUM_PROCESS_BUFS) buf0_num = BEGINNING;
    }
}

void Check_Process_Buffers(void){
    int i;  // buf_num
    int j;  // buf_index
    if (ProcessBuf_rd != buf0_num){
        char first_char = UCA0_Process_Buf[ProcessBuf_rd][BEGINNING];   // get first char of buffer
        char second_char = UCA0_Process_Buf[ProcessBuf_rd][BEGINNING + 1];   // get second char of buffer

        switch (first_char){
            case '^':
                switch (second_char){
                    case '^':
                        // Transmit back to PC "I'm Here"
                        UCA1_transmit("Hi I'm here!\r\n");
                        break;
                    case 'F':
                        // change baud to 115200
                        Change_UCA_Baud('F');
                        UCA1_transmit("115,200 Baud Set\r\n");



                        for (i = 0; i < LARGE_BUFFER_SIZE; i++){
                            UCA0_Process_Buf[ProcessBuf_rd][i] = '\0';
                        }
                        //UCA0IFG &= ~UCRXIFG;

                        break;
                    case 'S':
                        // change baud to 9600

                        Change_UCA_Baud('S');
                        UCA1_transmit("9,600 Baud Set\r\n");

                        for (i = 0; i < LARGE_BUFFER_SIZE; i++){
                            UCA0_Process_Buf[ProcessBuf_rd][i] = '\0';
                        }

                        //UCA0IFG &= ~UCRXIFG;
                        break;
                    case 'T':
                        UCA1_transmit("TEST\r\n");
                        for (i = 0; i < LARGE_BUFFER_SIZE; i++){
                            UCA0_Process_Buf[ProcessBuf_rd][i] = '\0';
                        }
                    default:
                        break;
                }
                second_char = '\0';
//                clear buffers containing command

                break;

            default:
                break;
        }
        first_char = '\0';
        for (j = 0; j < RING_BUFFER_SIZE; j++){
            UCA0_Process_Buf[ProcessBuf_rd][j] = '\0';
        }

        ProcessBuf_rd++;
        if (ProcessBuf_rd >= NUM_PROCESS_BUFS) ProcessBuf_rd = BEGINNING;

    }
}








































