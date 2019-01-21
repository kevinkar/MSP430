#ifndef LED_H
#define LED_H

#include "main.h"

// Enables the led
void led_enable(PIN p);

// Disables the led
void led_disable(PIN p);

// Toggle the enable/disable state of the led
void led_tobble(PIN p);

// Turns on the led
void led_on(PIN p);

// Turns off the led
void led_off(PIN p);

// Toggles the state of the led
void led_toggle(PIN p);

// Led functions without arguments
// For easy use with function pointers
void redled_toggle(void);
void greenled_toggle(void);
void redled_enable(void);
void greenled_enable(void);
void redled_disable(void);
void greenled_disable(void);
void redled_on(void);
void greenled_on(void);
void redled_off(void);
void greenled_off(void);
void redled_tobble(void);
void greenled_tobble(void);

#endif
