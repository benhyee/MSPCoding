#include <string.h>
#include <terminal.h>
#include "msp.h"
#define FALSE 0
#define TRUE 1

//counts the number of bytes read into the buffer
int readCount = 0;
char terminalbufferReady;
int  terminalbuffer;
unsigned int columnCount;
unsigned int rowCount;

void terminal_init()
{
    EUSCI_A0->CTLW0 |= 1;
    EUSCI_A0->MCTLW = 0;
    EUSCI_A0->CTLW0 = 0x0081;
    EUSCI_A0->BRW = 208;
    P1->SEL0 |= 0x0C;
    P1->SEL1 &= ~0x0C;
    EUSCI_A0->CTLW0 &= ~1;
    EUSCI_A0->IE |= 1;
}

void terminal_transmitChar(char character)
{
    while(!(EUSCI_A0->IFG & 0x02)) { }
    EUSCI_A0->TXBUF = character;
}

void terminal_transmitWord(char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        terminal_transmitChar(word[i]);
    }
}

void terminal_transmitInt(int input)
{
    terminal_transmitChar((input / 10000) + 48);
    terminal_transmitChar(((input / 1000) % 10) + 48);
    terminal_transmitChar(((input / 100) % 10) + 48);
    terminal_transmitChar(((input / 10) % 10) + 48);
    terminal_transmitChar((input % 10) + 48);
    terminal_transmitChar('\r');
    //terminal_transmitChar('\n');
}

void terminal_transmitDouble(double input)
{
    if ( input < 0)
    {
        input = 0;
    }
        terminal_transmitChar(((int) (input/10000)%10) + 48);
        terminal_transmitChar(((int) (input/1000)%10) + 48);
        terminal_transmitChar(((int) (input/100)%10) + 48);
        terminal_transmitChar(((int) (input/10)%10) + 48);
        terminal_transmitChar(((int) (input)%10) + 48);

        terminal_transmitChar('V');
        terminal_transmitChar('\r');
        terminal_transmitChar('\n');

}

int terminal_receiveInt()
{
    char result = terminalbuffer;
    terminalbuffer = 0;
    terminalbufferReady = FALSE;
    return result;
}


void EUSCIA0_IRQHandler()
{
    unsigned int result = EUSCI_A0->RXBUF;
    terminal_transmitChar((char)result);
    if(result == 91 && txDataFlag == FALSE)
    {
        terminalbufferReady = TRUE;
        rowCount = 0;
        columnCount = 0;
        txDataFlag = TRUE;
        return;
    }
    if(result == 91 && txDataFlag == TRUE)
    {
        terminalbufferReady = TRUE;
        rowCount++;
        columnCount = 0;
        return;
    }



    else if(result == 44 && txDataFlag == TRUE)
    {
        terminalbufferReady = TRUE;
        columnCount++;
        return;
    }

    else if(result<48 || result > 57)
    {
        return;
    }
    terminalbuffer = (terminalbuffer * 10) + (result - 48);

}
