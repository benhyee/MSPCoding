/*
 * spi.c
 *
 *  Created on: Feb 23, 2018
 *      Author: Ben Yee
 */
#include "msp.h"

void SPI_init(){
    // DCO = 24 MHz, SMCLK and MCLK = DCO
    CS->KEY = CS_KEY_VAL;
    CS->CTL0 = 0;
    CS->CTL0 = CS_CTL0_DCORSEL_4;   // DCO = 24 MHz
    CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    CS->KEY = 0;

    // Configure port bits for SPI
    P4->DIR |= BIT1;                     // Will use BIT4 to activate /CE on the DAC
    P1SEL0 |= BIT6 + BIT5;               // Configure P1.6 and P1.5 for UCB0SIMO and UCB0CLK
    P1SEL1 &= ~(BIT6 + BIT5);            //

    // SPI Setup
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;   // Put eUSCI state machine in reset

    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST |   // Remain eUSCI state machine in reset
                    EUSCI_B_CTLW0_MST   |   // Set as SPI master
                    EUSCI_B_CTLW0_SYNC  |   // Set as synchronous mode
                    EUSCI_B_CTLW0_CKPL  |   // Set clock polarity high
                    EUSCI_B_CTLW0_MSB;      // MSB first

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SSEL__SMCLK; // SMCLK
    EUSCI_B0->BRW = 0x01;                         // divide by 16, clock = fBRCLK/(UCBRx)
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;      // Initialize USCI state machine, SPI
                                                // now waiting for something to
                                                // be placed in TXBUF

    EUSCI_B0->IFG |= EUSCI_B_IFG_TXIFG;  // Clear TXIFG flag
}

