#ifndef TIMER_H
#define TIMER_H

// Interval value for the timer 125 = 1ms w/ 1Mhz
#define TIMER_INTERVAL 125

#define TIMER_TICKS 1

static const unsigned int TIMER_DELAY = TIMER_INTERVAL * TIMER_TICKS;

#include "main.h"

// Initializes timer with given delay
void timer_init(void);

#endif
