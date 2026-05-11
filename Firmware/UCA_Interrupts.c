//******************************************************************************
// File Name:   UCA_Interrupts.c
// Description: Universal Communication Interface (eUSCI_A). Handles
//              asynchronous serial communication and ring buffer interrupts.
// Author:      Luca
//******************************************************************************

#include "ProjectMaster.h"

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
//-----------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
    switch(__even_in_range(UCA0IV,0x08)){
        case 0:// Vector 0 - no interrupt
            break;

        case 2: // Vector 2 - RXIFG
            rx_char = UCA0RXBUF;
            UCA0_RX_Ring_Buf[UCA0_RX_wr] = rx_char;   // Get received char and store in ring buf
            UCA0_RX_wr++;       // increment write index

            // check for wrap around
            if (UCA0_RX_wr >= RING_BUFFER_SIZE) UCA0_RX_wr = BEGINNING;
            if (rx_char == '^') command_state = ON;
            if (!command_state) {
                //UCA1IE |= UCTXIE;
                UCA1TXBUF = rx_char;
            }

            break;

        case 4: // Vector 4 - TXIFG
            if (UCA0_TX_Ring_Buf[UCA0_TX_rd] != '\n'){
                UCA0TXBUF = UCA0_TX_Ring_Buf[UCA0_TX_rd];
                UCA0_TX_rd++;
                if (UCA0_TX_rd >= RING_BUFFER_SIZE) UCA0_TX_rd = BEGINNING;
            }
            else {
                UCA0TXBUF = '\n';
                UCA0IE &= ~UCTXIE;  // Done transmitting
                //UCA0_TX_rd = 0;
            }

            break;

        default: break;
    }
//------------------------------------------------------------------------------
}


#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
//-----------------------------------------------------------------------------
// Echo back RXed character, confirm TX buffer is ready first
    switch(__even_in_range(UCA1IV,0x08)){
        case 0: break; // Vector 0 - no interrupt

        case 2: // Vector 2 - RXIFG
            rx_char = UCA1RXBUF;
            UCA1_RX_Ring_Buf[UCA1_RX_wr] = rx_char;   // Get received char and store in ring buf
            usb_active = ON;

            UCA1_RX_wr++;       // increment write index
            // check for wrap around
            if (UCA1_RX_wr >= RING_BUFFER_SIZE) UCA1_RX_wr = BEGINNING;



//            Pass to UCA0TX (IoT)
            if (usb_active) {
                //UCA0IE |= UCTXIE;
                UCA0TXBUF = rx_char;
            }

            break;

        case 4: // Vector 4 - TXIFG
            //UCA1IE &= ~UCTXIE;
            transmit_done = NO;
            if (UCA1_TX_Ring_Buf[UCA1_TX_rd] != '\0'){
                UCA1TXBUF = UCA1_TX_Ring_Buf[UCA1_TX_rd];
                UCA1_TX_rd++;

                if (UCA1_TX_rd >= RING_BUFFER_SIZE) UCA1_TX_rd = BEGINNING;
            }
            else {
                transmit_done = YES;
                UCA1IE &= ~UCTXIE;  // Done transmitting
                UCA1_TX_rd = BEGINNING;
            }

            break;

        default: break;
    }
//------------------------------------------------------------------------------
}


