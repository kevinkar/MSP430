#ifndef UART_H
#define UART_H

#include "main.h"

// Initializes UART for use
void UART_Init();

// Sends single byte over UART
void UART_SendByte(tByte c);

// Sends string of characters with UART_SendByte
void UART_Write(char *);

// Reads character from the RX buffer
tByte UART_Read(char *, tByte max);

#endif
