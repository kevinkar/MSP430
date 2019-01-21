#ifndef LED_H
#define LED_H

#include "tlight.h"

// Enables the led.
void led_enable(PIN p);

// Disables the led.
void led_disable(PIN p);

// Toggle the enable/disable state of the led.
void led_tobble(PIN p);

// Turns on the led.
void led_on(PIN p);

// Turns off the led.
void led_off(PIN p);

// Toggles the state of the led.
void led_toggle(PIN p);

#endif
