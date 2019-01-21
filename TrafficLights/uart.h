#ifndef UART_H
#define UART_H

#include "tlight.h"

/*
 * UART definitions
 */
#define RXD PIN1
#define TXD PIN2
#define UART_BUFFER 64

// Initializes UART for use.
void uart_init();

// Receives characters to be sent.
void uart_write(char *);

// Save the received characters in the given array.
tByte uart_read(char *, tByte max);

void uart_sendbyte(tByte tosend);

tByte uart_readbyte(void);

// Put character in the TX or overload buffer.
inline void uart_putc(tByte c);

// Save character from RX buffer to overload buffer.
inline tByte uart_getc();

#endif
