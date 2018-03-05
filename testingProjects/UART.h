/*
 * UART.h
 *
 *  Created on: Mar 4, 2018
 *      Author: Ben Yee
 */

#ifndef UART_H_
#define UART_H_


void terminal_init();
void terminal_transmitChar(char character);
void terminal_transmitWord(char *word);
void terminal_transmitInt(int input);
void terminal_transmitDouble(double input);
char terminal_receiveChar();
int terminal_receiveInt();


#endif /* UART_H_ */
