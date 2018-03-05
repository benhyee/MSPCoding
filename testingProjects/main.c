#include "msp.h"
#include "delay.h"
#include "spi.h"
#include "dacFuncs.h"
#include "UART.h"
#define CURRENT_FREQ FREQ_24_MHZ
#define SLAVE_ADDR 0x68
/**
 * main.c
 */
volatile unsigned int TempDAC_Value = 0;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	set_DCO(CURRENT_FREQ);
	SPI_init();
	I2C1_init();
	P5->SEL1 &= ~15;
	P5->SEL0 &= ~15;
	P5->DIR |= 15;

	while(1){
	    P5->OUT &= 1;
	    P5->OUT |= 1;

        Drive_DAC(TempDAC_Value);
        P5->OUT &= 1;
        P5->OUT &= 2;
        P5->OUT |= 2;
        P5->OUT |= 1;

        TempDAC_Value = 254;
        P5->OUT &= 1;
        P5->OUT |= 1;

        Drive_DAC(TempDAC_Value);
        P5->OUT &= 1;
        P5->OUT &= 2;
        P5->OUT |= 2;
        P5->OUT |= 1;

        TempDAC_Value = 0;

	}
}
