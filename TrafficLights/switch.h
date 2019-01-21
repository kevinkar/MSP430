#ifndef SWITCH_H
#define SWITCH_H

#include "tlight.h"

// Initializes pin as switch (input).
void switch_init(PIN p);

// Initializes switch with interrupts enabled.
void switch_initwie(PIN p);

// Checks current state of switch.
int switch_pressed(PIN p);

// Toggle enable/disable state of LEDs on button press AKA TASK3
void switch_check(void);

#endif
