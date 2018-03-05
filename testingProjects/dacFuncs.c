/*
 * dacFuncs.c
 *
 *  Created on: Mar 4, 2018
 *      Author: Ben Yee
 */


#include "msp.h"
#include "spi.h"

void Drive_DAC(unsigned int level){
  unsigned int DAC_Word = 0;

  DAC_Word =level & 0x00FF;   // 0x1000 sets DAC for Write
                                            // to DAC, Gain = 2, /SHDN = 1
                                            // and put 12-bit level value
                                            // in low 12 bits.

  DAC_Word =level | 0x0300;


  EUSCI_B0->TXBUF = (unsigned char) (DAC_Word >> 8);  // Shift upper byte of DAC_Word
                                                      // 8-bits to right

  while (!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));              // USCI_A0 TX buffer ready?
  EUSCI_B0->TXBUF = (unsigned char) (DAC_Word & 0x00FF);  // Transmit lower byte to DAC
  while (!(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG));      // Poll the TX flag to wait for completion


  return;
}
