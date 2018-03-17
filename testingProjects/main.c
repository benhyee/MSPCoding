#include "msp.h"
#include "delay.h"
#include "spi.h"
#include "dacFuncs.h"
#include "timer.h"
#include "terminal.h"

#define CURRENT_FREQ FREQ_24_MHZ
#define SLAVE_ADDR 0x68

#define FALSE 0
#define TRUE 1

volatile unsigned int TempDAC_Value = 0;
int itemCount;

void main(void)
{
    __disable_irq();
	set_DCO(CURRENT_FREQ);
	SPI_init();
    P5->SEL1 &= ~0xFF;
    P5->SEL0 &= ~0xFF;
    P5->DIR |= 0xFF;
    terminal_init();
    NVIC_SetPriority(EUSCIA0_IRQn, 4);
    NVIC_EnableIRQ(EUSCIA0_IRQn);
    __enable_irq();
    unsigned int dacBuffer[23];
//	int step;
    int i;
//	int *sinePoint;
//    sinePoint = computeSin();
	while(1){
	    if(terminalbufferReady == TRUE)
	    {
	        dacBuffer[itemCount] = terminal_receiveInt();
	        itemCount++;
	        if(itemCount > 22)
	        {
	            for( i = 1; i < 15; i++)
	            {
	                Drive_DAC(*(dacBuffer + i),1,FALSE);

	            }
                itemCount = 0;
	        }
	    }

//            TempDAC_Value = 255;
//            Drive_DAC(TempDAC_Value,1,FALSE);
//            Drive_DAC(TempDAC_Value,1,TRUE);
//            Drive_DAC(TempDAC_Value,2,FALSE);
//            Drive_DAC(TempDAC_Value,2,TRUE);
//            Drive_DAC(TempDAC_Value,0x04,FALSE);
//            Drive_DAC(TempDAC_Value,0x04,TRUE);
//            Drive_DAC(TempDAC_Value,0x10,FALSE);
//            Drive_DAC(TempDAC_Value,0x10,TRUE);
//            TempDAC_Value = 0;
//            Drive_DAC(TempDAC_Value,1,FALSE);
//            Drive_DAC(TempDAC_Value,1,TRUE);
//            Drive_DAC(TempDAC_Value,2,FALSE);
//            Drive_DAC(TempDAC_Value,2,TRUE);
//            Drive_DAC(TempDAC_Value,0x04,FALSE);
//            Drive_DAC(TempDAC_Value,0x04,TRUE);
//            Drive_DAC(TempDAC_Value,0x10,FALSE);
//            Drive_DAC(TempDAC_Value,0x10,TRUE);

	}
}
