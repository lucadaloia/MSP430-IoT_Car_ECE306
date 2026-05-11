/*
 * UCA.h
 *
 *  Created on: Mar 27, 2026
 *      Author: Luca
 */

#ifndef UCA_H_
#define UCA_H_

void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

void Change_UCA_Baud(char speed);
void UCA1_transmit(char* string);
void UCA1_Process(void);
void Check_Process_Buffers(void);
void UCA0_Process(void);
void heart_beat(void);
void UCA0_baud(char baud_speed);


#endif /* UCA_H_ */
