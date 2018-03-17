#ifndef TERMINAL_H
#define TERMINAL_H

extern char terminalbufferReady;
extern int terminalBuffer;
void terminal_init();
void terminal_transmitChar(char character);
void terminal_transmitWord(char *word);
void terminal_transmitInt(int input);
void terminal_transmitDouble(double input);
int terminal_receiveInt();
void EUSCIA0_IRQHandler();

#endif
