/*  Author: Kadapanatham Shashank Rao, Vangoor Vineeth Kumar Reddy
 *  timer.h
 *
 *  Created on: 07-Apr-2018
 *
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

extern uint16_t flag;

void init_func();
void Init_timer_A(void);
void Run_Timer_Interrupt_CCIFG(void);
void Init_timer_no_interrupts(void);
void Timer_Delay_20ms(void);
void Timer_Delay_300ms(uint8_t delay_time);

#endif /* TIMER_H_ */
