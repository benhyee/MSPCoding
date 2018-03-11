/*
 * dacFuncs.c
 *
 *  Created on: Mar 4, 2018
 *      Author: Ben Yee
 */


#include "msp.h"
#include "spi.h"
#include <math.h>
#define FALSE 0
#define TRUE 1

void Drive_DAC(unsigned int level, unsigned int channel, unsigned int toggle){
  unsigned int DAC_Word = 0;

  if(toggle == FALSE)
  {
      DAC_Word =level | 0x8300;
  }
  else if(toggle == TRUE)
  {
      DAC_Word =level | 0x8700;
  }
  else{
      DAC_Word = 0;
  }

  P5 -> OUT |= channel;
  P5 -> OUT &= ~channel;

  EUSCI_B0->TXBUF = (unsigned char) (DAC_Word >> 8);  // Shift upper byte of DAC_Word
                                                      // 8-bits to right
  while (!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));              // USCI_A0 TX buffer ready?
  EUSCI_B0->TXBUF = (unsigned char) (DAC_Word & 0x00FF);  // Transmit lower byte to DAC
  while (!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));      // Poll the TX flag to wait for completion


  P5 -> OUT |= channel;
  P5 -> OUT &= ~channel;

  return;
}

int *computeSin()
{
    static int sinewave[50];
    double radians = 2.0 * 3.1415926;
    double step = radians / 50.0;
    double value = 0;
    int i;

    for (i = 0; i < 50; i++)
    {
        sinewave[i] = 128 + (128 * sin(value));//
        value += step;
    }
    return sinewave;
}
