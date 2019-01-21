#ifndef TIMER_H
#define TIMER_H

#include "tlight.h"

// Defines 1 millisecond intervall depending on frequency
#define TIMER_INTERVAL (DCO_FREQ/DCO_DIV/1000)
// Amount of milliseconds in the timer
#define TIMER_TICKS 500

#define TIMER_DELAY (TIMER_INTERVAL*TIMER_TICKS)

// Initializes timer with delay defined here.
void timer_init(void);

#endif
