/*  Author: Kadapanatham Shashank Rao, Vangoor Vineeth Kumar Reddy
 *  main.c
 *
 *  Created on: 07-Apr-2018
 *
 */
#include <msp430g2553.h>
#include <stdint.h>
#include"timer.h"
#include"motor.h"
#include"adc.h"

void init_motor()
{
    P2DIR |= BIT1; // Initialize direction for motor
    P2DIR |= BIT2; // Initialize pwm output for motor
    P2SEL |= BIT2; // P2sel is set to 1
    P2SEL2 &=~ BIT2; // P2sel2 is set to 0, this combination is to generation PWM signal

    P2DIR |= BIT5; // Initialize direction for motor
    P2DIR |= BIT4; // Initialize pwm output for motor
    P2SEL |= BIT4; // P2sel is set to 1
    P2SEL2&=~ BIT4; // P2sel2 is set to 0, this combination is to generation PWM signal

    TA1CTL=0;
    TA1CTL|=(MC_1|ID_0|TACLR|TASSEL_2);
    TA1CCR0=10000; // Maximum speed using frequency
	//TA1CCTL1= OUTMOD_7; // Output mode = set reset
    //TA1CCR1=speed1;
}

void main(void)
{

     WDTCTL = WDTPW | WDTHOLD;
     init_func();
     Init_timer_no_interrupts();
     init_motor();
     Init_timer_A();
     Run_Timer_Interrupt_CCIFG();

     __enable_interrupt();
     __delay_cycles(10000);

     while(1)
     {
        if (flag % 2 != 0) // Check if button is pressed
        {
            if (firstDetect == 0) // The whirlpool path goes on until an object is detected
            {
                whirlpool();
            }
            rightIR();
            leftIR();
        }
        if(flag % 2 == 0)
        {
            stop();
        }
     }
}
