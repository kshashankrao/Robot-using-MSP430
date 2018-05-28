/*  Author: Kadapanatham Shashank Rao, Vangoor Vineeth Kumar Reddy
 *  motor.h
 *
 *  Created on: 07-Apr-2018
 *
 */
#ifndef MOTOR_H_
#define MOTOR_H_
#include<stdint.h>

extern uint16_t firstDetect ;

void init_motor();

void wheelLeft(int16_t speed1,int16_t dir1);
void wheelRight(int16_t speed2,int16_t dir2);

void straight();
void stop();
void left();

void rightIR();
void leftIR();

void whirlpool();

#endif /* MOTOR_H_ */
