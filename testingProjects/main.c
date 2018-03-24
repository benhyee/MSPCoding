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
unsigned int columnCount;
unsigned int rowCount;
char txDataFlag = 0;
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
    unsigned char dacBuffer[65000];
    unsigned int i = 0;
//	int step;
//	int *sinePoint;
//    sinePoint = computeSin();
	while(1){
	    if(terminalbufferReady == TRUE)
	    {
	        *(dacBuffer + rowCount*8+columnCount) = terminal_receiveInt();
	        if(rowCount > 8124)
	        {
	            for(i = 1; i < 8124; i ++)
	            {
                    Drive_DAC(*(dacBuffer + 8*(i-1)+1),1,FALSE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+2),1,TRUE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+3),2,FALSE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+4),2,TRUE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+5),0x04,FALSE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+6),0x04,TRUE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+7),0x10,FALSE);
                    Drive_DAC(*(dacBuffer + 8*(i-1)+8),0x10,TRUE);
	            }

                Drive_DAC(0,1,FALSE);
                Drive_DAC(0,1,TRUE);
                Drive_DAC(0,2,FALSE);
                Drive_DAC(0,2,TRUE);
                Drive_DAC(0,0x04,FALSE);
                Drive_DAC(0,0x04,TRUE);
                Drive_DAC(0,0x10,FALSE);
                Drive_DAC(0,0x10,TRUE);

                txDataFlag = FALSE;
	        }
	    }


	}
}
