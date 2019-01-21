#ifndef SWITCH_H
#define SWITCH_H

#include "main.h"

/*
 * Initialize pin as switch (input)
 */
void switch_init(PIN p);

/*
 * Initialize switch with interrupts enabled
 */
void switch_initwie(PIN p);

/*
 * Checks and returns current state of switch
 */
int switch_pressed(PIN p);

/*
 * May be called on switch interrupt
 */
void switch_action(void);

/*
 * ISR for switch interrupt
 */
void PORT1_ISR(void);

#endif
