#ifndef MAIN_H
#define MAIN_H

/*
 * typedefs need to be before includes
 */
typedef unsigned int PIN;
typedef unsigned char tByte;
typedef unsigned int tWord;

/*
 * INCLUDE HEADERS
 * Board header
 * Standard library headers
 * Project headers
 */
#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include "alien.h"
#include "port.h"
#include "sound.h"
#include "switch.h"
#include "timer.h"
#include "uart.h"

/*
 * DCO (or CPU) Frequency, 1Mhz, 8Mhz or 16Mhz
 */
//#define DCO_FREQ 16000000     // 16 Million Hertz
#define DCO_FREQ 1000000        // 1 Million Hertz

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

volatile tWord switchflag;
volatile tWord firstrun;

/*
 * Main superloop
 */
void main(void);

/*
 * Resets the whole system
 */
void restart(void);

#endif
