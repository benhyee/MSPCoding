#include "msp.h"
#include "delay.h"
#include "spi.h"
#include "dacFuncs.h"
#include "timer.h"
#include "UART.h"
#define CURRENT_FREQ FREQ_24_MHZ
#define SLAVE_ADDR 0x68

#define FALSE 0
#define TRUE 1
/**
 * main.c
 */
volatile unsigned int TempDAC_Value = 0;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	set_DCO(CURRENT_FREQ);
	SPI_init();
	terminal_init();
//    timer_init();
	P5->SEL1 &= ~0xFF;
	P5->SEL0 &= ~0xFF;
	P5->DIR |= 0xFF;
	int step;
	int *sinePoint;
    sinePoint = computeSin();

    //__enable_irq();
	while(1){
        terminal_transmitChar('A');
        for(step = 0; step< 50; step++)
        {
          TempDAC_Value = *(sinePoint + step);
          Drive_DAC(TempDAC_Value,1,FALSE);
          Drive_DAC(TempDAC_Value,1,TRUE);
          Drive_DAC(TempDAC_Value,2,FALSE);
          Drive_DAC(TempDAC_Value,2,TRUE);
          Drive_DAC(TempDAC_Value,0x04,FALSE);
          Drive_DAC(TempDAC_Value,0x04,TRUE);
          Drive_DAC(TempDAC_Value,0x10,FALSE);
          Drive_DAC(TempDAC_Value,0x10,TRUE);
        }
//          __sleep();
	}
}
