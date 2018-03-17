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
    int dacBuffer[9];

//	int step;
//	int *sinePoint;
//    sinePoint = computeSin();
	while(1){
	    if(terminalbufferReady == TRUE)
	    {
	        dacBuffer[itemCount] = terminal_receiveInt();
	        itemCount++;
	        if(itemCount > 8)
	        {
//	            Drive_DAC(dacBuffer[1],0x01,FALSE);
//                Drive_DAC(dacBuffer[2],0x01,TRUE);
//                Drive_DAC(dacBuffer[3],0x02,FALSE);
//                Drive_DAC(dacBuffer[4],0x02,TRUE);
//                Drive_DAC(dacBuffer[5],0x04,FALSE);
//                Drive_DAC(dacBuffer[6],0x04,TRUE);
//                Drive_DAC(dacBuffer[7],0x10,FALSE);
//                Drive_DAC(dacBuffer[8],0x10,TRUE);
                itemCount = 0;
	        }
	    }

//        Drive_DAC(TempDAC_Value,0x10,TRUE);
	}
}
