#ifndef SWITCH_H
#define SWITCH_H

#include "main.h"

// Initializes pin as switch (input)
void switch_init(PIN p);

// Initializes switch with interrupts enabled
void switch_initwie(PIN p);

// Checks current state of switch
int switch_pressed(PIN p);

#endif
