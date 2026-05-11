/*
 * movement.h
 *
 *  Created on: Mar 2, 2026
 *      Author: Luca
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

// movement functions
void stop_all(void);
void move_forward(void);
void move_reverse(void);
void spin_right(void);
void spin_left(void);

// safety function
void check_motor_safety(void);

//PID
void update_motors(int correction);
void Black_Line(void);
long u(void);

#endif /* MOVEMENT_H_ */
