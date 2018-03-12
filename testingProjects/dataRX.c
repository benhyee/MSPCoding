/*
 * dataRX.c
 *
 *  Created on: Mar 11, 2018
 *      Author: User
 */

#include "msp.h"


char  RXCharbuffer;

void dataRX_init()
{
    EUSCI_A2 -> CTLW0 |= 1;
    EUSCI_A2 -> MCTLW = 0;
    EUSCI_A2 -> CTLW0 = 0x0081;
    EUSCI_A2 -> BRW = 26;
    P3->SEL0 |= 0x0C;
    P3->SEL1 &= ~0x0C;
    EUSCI_A2 -> CTLW0 &= ~1;
}

void RX_Char()
{
    while(!(EUSCI_A2 ->IFG & 0x01)){}
    RXCharbuffer = EUSCI_A2 -> RXBUF;
}
void TX_Char(char character)
{
    while(!(EUSCI_A2 -> IFG & 0x02)) {}
    EUSCI_A2 -> TXBUF = character;
}

