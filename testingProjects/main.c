#include "msp.h"
#include "delay.h"
#include "spi.h"
#define CURRENT_FREQ FREQ_24_MHZ
/**
 * main.c
 */
volatile unsigned int TempDAC_Value = 0;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	set_DCO(CURRENT_FREQ);
	SPI_init();
	P2->SEL1 &= ~2;
	P2->SEL0 &= ~2;
	P2->DIR |= 2;
	while(1){
	      Drive_DAC(TempDAC_Value);
	      TempDAC_Value += 100;            // increment by 100 mv
	}
}
