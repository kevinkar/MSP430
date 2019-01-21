/*
 * Synchronized traffic lights
 *
 */

#ifndef TLIGHT_H
#define TLIGHT_H

/*
 * PORT, LED, SWITCH, UART typedef
 * NEED TO BE BEFORE INCLUDES
 */
typedef unsigned int PIN;
typedef unsigned char tByte;
typedef unsigned int tWord;

/*
 * INCLUDE HEADERS
 * Board header
 * Project headers
 */
#include <msp430.h>
#include "led.h"
#include "port.h"
#include "scheduler.h"
#include "state.h"
#include "switch.h"
#include "timer.h"
#include "uart.h"

/*
 * MAIN definitions
 */
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define XERO 0x0000

#define MASTER 0
#define SLAVE 1

/*
 * PORT definitions
 */
#define PIN0 BIT0
#define PIN1 BIT1
#define PIN2 BIT2
#define PIN3 BIT3
#define PIN4 BIT4
#define PIN5 BIT5
#define PIN6 BIT6
#define PIN7 BIT7

/*
 * LED definitions
 */
#define LED1 PIN0
#define LED2 PIN6
#define REDLED LED1
#define GREENLED LED2
/*
 * SWITCH definitions
 */
#define SW1 PIN3

#define STRING_SIZE 8
// Assign static pointers for default text pieces
// DEFINES char pointers for our predefined messages
// NEWLINE. Here CR + LF. Steps on some terminals
static char *NL = "\r\n";

static tWord gopmode;

#define DCO_FREQ 1000000     // 1 Million Hertz
#define DCO_DIV 8           // DCO divider, 8

// Main function
void main(void);

void master_init(void);

void slave_init(void);

// Timer interrupt calls this function
void timer_action(void);

// Switch interrupt calls this function
void switch_action(void);

void send_newline(void);

#endif
