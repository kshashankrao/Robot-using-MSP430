/*  Author: Kadapanatham Shashank Rao, Vangoor Vineeth Kumar Reddy
 *  motor.c
 *
 *  Created on: 07-Apr-2018
 *
 */
#include <msp430g2553.h>
#include <stdint.h>
#include  "adc.h"
#include "timer.h"
#include "motor.h"

const int16_t maxspeed = 10000;
int16_t minspeed = 200;
int16_t i;
const uint16_t distanceStop = 600 ;
uint16_t firstDetect = 0;

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
}

void wheelLeft(int16_t speed1,int16_t dir1)
{
    TA1CCTL1= OUTMOD_7; // Output mode = set reset
    TA1CCR1=speed1;

    if(dir1 == 1)
    {
       P2OUT |= BIT1;
    }
    if(dir1 == 0)
    {
       P2OUT&=~ BIT1;
    }
}

void wheelRight(int16_t speed2,int16_t dir2)
{
    TA1CCTL2= OUTMOD_7; // Output mode = set reset
    TA1CCR2=speed2;

    if(dir2 == 0)
     {
         P2OUT |= BIT5;
     }
     if(dir2 == 1)
     {
         P2OUT&=~ BIT5;
     }
}

void stop()
{
    wheelLeft(0,0);
    wheelRight(0,0);
}

void straight()
{
    wheelLeft(7000,0);
    wheelRight(7000,0);
}


void left()
{
		wheelLeft(5000,1);
	    wheelRight(5000,0);
	    Timer_Delay_300ms(4);
}
void rightIR()
{
        uint16_t irR = read_adc(5);
        if((irR < distanceStop))
        {
            straight();
            //Timer_Delay_20ms();
        }
        else
        {
            stop();
            Timer_Delay_20ms();
            left();
            Timer_Delay_20ms();
        }
}

void leftIR()
{
        uint16_t irL = read_adc(4);
        if(irL < distanceStop)
        {
            straight();
            //Timer_Delay_20ms();
        }
        else
        {
            stop();
            Timer_Delay_300ms(2);
            left();
            Timer_Delay_20ms();
        }
}



void whirlpool() // Function to run the robot in a whirlpool shape
{
	  for(i=0; i<2000;i++)
	   {
	                uint16_t irRtest = read_adc(5);
	                uint16_t irLtest = read_adc(4);
	                wheelRight(maxspeed,0);
					wheelLeft(minspeed,0);

					minspeed ++;
					if(minspeed > 8000)
					{
					    minspeed = 8001;
					}

					if ((irRtest > distanceStop) || (irLtest > distanceStop))
					{
					    firstDetect = 1;
					    stop();
					}
					__delay_cycles(1000);
	    }
}
