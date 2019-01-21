#ifndef UART_H
#define UART_H

#include "main.h"

/*
 * UART definitions
 */
#define RXD PIN1
#define TXD PIN2

/*
 * Initialize UART for use
 */
void uart_init();

/*
 * Send a string over UART
 */
void uart_write(char *str);

#endif
