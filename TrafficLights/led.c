#include "led.h"

// Enables the led.
void led_enable(PIN p) {
    pdir_out(p);
}

// Disables the led.
void led_disable(PIN p) {
    pdir_in(p);
}

// Toggle the enable/disable state of the led.
void led_tobble(PIN p) {
    pdir_toggle(p);
}

// Turns on the led.
void led_on(PIN p) {
    p_high(p);
}

// Turns off the led.
void led_off(PIN p) {
    p_low(p);
}

// Toggles the state of the led.
void led_toggle(PIN p) {
    p_toggle(p);
}
