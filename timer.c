/*  Author: Kadapanatham Shashank Rao, Vangoor Vineeth Kumar Reddy
 *  timer.c
 *
 *  Created on: 07-Apr-2018
 *
 */
#include <msp430g2553.h>
#include <stdint.h>
#include"timer.h"
#include"motor.h"

uint16_t flag = 0;

void init_func()
{
    P1SEL &= ~(BIT3|BIT6 |BIT0);
    P1SEL2 &= ~(BIT3|BIT6|BIT0);
    P1DIR &= ~ (BIT3);

    P1REN |= (BIT3);
    P1OUT |= BIT3;

    P1IE |= BIT3;
    P1IES &= ~BIT3;
    P1IFG &= ~BIT3;

    P1DIR |= BIT6;
    P1OUT &= ~BIT6;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
}

void Init_timer_no_interrupts(void)
{
	TACCR0=20000;
	TACTL=0;
	TACTL|=TASSEL_2|ID_3; // Using smclock and divide frequency by 8
}

/*void Timer_Delay_20ms(void) //Timer for 20 ms delay
{
	TACTL|=MC_1|TACLR; // Start clock
	while((TACTL&TAIFG)==0);
	TACTL&=~TAIFG; // Clear Interrupt flag
	TACTL&=~(MC1|MC0); // Stop clock
}
*/
void Timer_Delay_20ms(void) //Timer for 20 ms delay
{
    __delay_cycles(200000);
}
void Timer_Delay_300ms(uint8_t delay_time) // Timer for specific amount of delay
{
	uint8_t i;
	for(i=0;i<delay_time;i++)
	{
		Timer_Delay_20ms();
	}
}

#pragma vector=PORT1_VECTOR
__interrupt void intSwitch()
{
        if ((P1IFG & BIT3) != 0) // If interrupt flag is set then flag++
        {
            Timer_Delay_300ms(15);
            P1OUT ^= BIT6;
            flag ++;
            P1IFG &= ~BIT3;
        }
}

void Init_timer_A(void)
{
    TACTL=0;
    TACTL|=(TASSEL_2|ID_3|TACLR);
    TACCR0=60000;
    TACCTL0=0;
    TACCTL0|=CCIE;


}
void Run_Timer_Interrupt_CCIFG(void)
{
    TACTL&=~TAIFG;
    TACTL|=MC_1|TACLR;
}
#pragma vector=TIMER0_A0_VECTOR   //INTERUPT  FUNCTION ON timer
__interrupt void interruptOnTimerA()
{
    static int checkStop=0;
    checkStop++;
    if (checkStop == 100)
    {

        while(1)
        {
            stop();
        }
    }
}
