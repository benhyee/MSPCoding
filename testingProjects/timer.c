/*
 * timer.c
 *
 *  Created on: Mar 10, 2018
 *      Author: Ben Yee
 */

#include "msp.h"
#include "dacFuncs.h"


#define FALSE 0
#define TRUE 1


void timer_init()
{

    P3->SEL1 &= ~BIT0;
    P3->SEL0 &= ~BIT0;
    P3->DIR |= BIT0;
    P3->OUT |= BIT0;
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] =2;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | // SMCLK, continuous mode
               TIMER_A_CTL_MC__UP;

//    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;    // Enable sleep on exit from ISR

    // Enable global interrupt
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
    __enable_irq();


}

void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    P3-> OUT ^= BIT0;
    __disable_irq();
}


