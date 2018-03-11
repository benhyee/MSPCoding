/*
 * UART.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Ben Yee
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_


void terminal_init();
void terminal_transmitChar(char character);
void terminal_transmitWord(char *word);
void terminal_transmitInt(int input);
void terminal_transmitDouble(double input);
char terminal_receiveChar();
int terminal_receiveInt();


#endif /* TERMINAL_H_ */
