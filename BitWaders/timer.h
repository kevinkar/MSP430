#ifndef TIMER_H
#define TIMER_H

#include "main.h"

#define TIMER_DIV 8     // DCO divider, 8
// Defines one millisecond interval depending on frequency
#define TIMER_INTERVAL (DCO_FREQ/TIMER_DIV/1000)
// Amount of milliseconds in the timer
#define TIMER_TICKS 500

#define TIMER_DELAY (TIMER_INTERVAL*TIMER_TICKS)

/*
 * Initialize timer with delay given here
 */
void timer_init(void);

/*
 * Start the timer interrupts
 */
void timer_startie(void);

/*
 * Stop the timer interrupts
 */
void timer_stopie(void);

/*
 * Reset the timer counter register
 */
void timer_resetcounter(void);

/*
 * May be called on timer interrupt
 */
void timer_action(void);

/*
 * ISR for timer interrupt
 */
void Timer_A(void);

#endif
