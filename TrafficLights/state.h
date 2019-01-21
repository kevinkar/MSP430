#ifndef STATE_H
#define STATE_H

typedef enum
{
    AMBER, RED, REDGREEN, GREENRED, GREEN
} tlight_state;

#include "tlight.h"

// Duration in counts of timer's <DELAY>
#define AMBER_DURATION 10
#define RED_DURATION 10
#define GREEN_DURATION 10
#define REDGREEN_DURATION 1
#define GREENRED_DURATION 1

#define TICK 22
#define ACK_TICK 6
/* FOR REAL USE
 #define GOTO_AMBER        20
 #define GOTO_RED          30
 #define GOTO_GREEN        40
 #define GOTO_REDGREEN     50
 #define GOTO_GREENRED     60

 #define GOTO_ERROR_0      10
 #define GOTO_ERROR_1      11
 #define GOTO_ERROR_2      12
 #define GOTO_ERROR_3      13

 #define ACK_AMBER         120
 #define ACK_RED           130
 #define ACK_GREEN         140
 #define ACK_REDGREEN      150
 #define ACK_GREENRED      160

 #define ACK_ERROR_0       110
 #define ACK_ERROR_1       111
 #define ACK_ERROR_2       112
 #define ACK_ERROR_3       113
 */
// VALUES FOR TESTING PURPOSES
#define GOTO_AMBER 48    //0
#define GOTO_RED 49      //1
#define GOTO_GREEN 50    //2
#define GOTO_REDGREEN 51 //3
#define GOTO_GREENRED 52 //4

#define GOTO_ERROR_0 10
#define GOTO_ERROR_1 11
#define GOTO_ERROR_2 12
#define GOTO_ERROR_3 13

#define ACK_AMBER 98     //b
#define ACK_RED 99       //c
#define ACK_GREEN 100    //d
#define ACK_REDGREEN 101 //e
#define ACK_GREENRED 102 //f

#define ACK_ERROR_0 110
#define ACK_ERROR_1 111
#define ACK_ERROR_2 112
#define ACK_ERROR_3 113

// save latest error message
static tByte error_message;

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

static tByte awaiting_ack;

static tByte received_ack;

static tByte received_message;

// Used to count our timer ticks in state machine
static tWord timer_ticks;

// Initializes traffic lights for use
void tlight_init();

void tlight_slave();

void tlight_master();

// Sets us into the correct state.
void tlight_update();

// Go from red to green(thru red+green)
void tlight_override();

#endif
