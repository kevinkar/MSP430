#ifndef TLIGHT_H
#define TLIGHT_H

#include "main.h"

/*
 * TLIGHT typedef
 */

typedef enum
{
    AMBER, RED, REDGREEN, GREENRED, GREEN
} tlight_state;

// Duration in counts of timer's <TIMER_DELAY> tick
#define AMBER_DURATION 10
#define RED_DURATION 10
#define GREEN_DURATION 10
#define REDGREEN_DURATION 1
#define GREENRED_DURATION 1
// DEFINES char pointers for our predefined messages
static char *AMBER_TEXT = "AMBER";
static char *RED_TEXT = "RED";
static char *GREEN_TEXT = "GREEN";
static char *REDGREEN_TEXT = "RED->GREEN";
static char *GREENRED_TEXT = "GREEN->RED";
static char *RED_OVERRIDE = "FORCED OVERRIDE";
/*
 * Alternatively use
 * extern char *ptrname; in .h
 * and assign in .c
 * char *ptrname = "text";
 */

// Keeps track of the state of the lights
static tlight_state current_state;

// Used to count our timer ticks in state machine
static int timer_ticks;

// Initializes traffic lights for use
void tlight_init();

// State machine counts timer ticks
void tlight_update();

// Go from red to green(thru red+green)
void tlight_override();

#endif
