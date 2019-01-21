/*
 * Programming Embedded Systems 2017
 * Exercise 3
 * This is the main header file. To make changes easier most things are managed here.
 * At this point we do have overglobalisation of variables. To be fixed...
 *
 */

#ifndef EX4_H
#define EX4_H
/*
 * PORT, LED, SWITCH, UART typedef
 * NEED TO BE BEFORE INCLUDES
 */
typedef unsigned int PIN;
typedef unsigned char tByte;
typedef unsigned int tWord;

#define TEMPERATURE_TRESHOLD 24
/*
 * INCLUDE HEADERS
 * Board header
 * Project headers
 */
#include <msp430.h>
#include "port.h"
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "tlight.h"
#include "uart.h"
#include "scheduler.h"
#include "adc.h"
#include "temp.h"

/*
 * MAIN definitions
 */
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define XERO 0x0000
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

/*
 * UART definitions
 */
#define TXD BIT2
#define RXD BIT1
#define BUFFER_SIZE 64
// Assign static pointers for default text pieces
// DEFINES char pointers for our predefined messages
// NEWLINE. Here CR + LF. Steps on some terminals
static char *NL = "\r\n";


//The maximum number of tasks at any one time
//during the execution of the program

/*
 * MAIN functions
 */
// Main function
void main(void);

void redled_toggle(void);

void greenled_toggle(void);

// Timer interrupt calls this function
void timer_action(void);

// Switch interrupt calls this function
void switch_action(void);

void scheduler_init(void);

void check_switch(void);

void send_newline(void);

void check_switch(void);

void check_temperature(void);

void send_temperature(void);

void prepare_temperature(void);

void blink_temperature(void);


#endif
