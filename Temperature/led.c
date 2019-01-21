#include "led.h"

// Enables the led
void led_enable(PIN p)
{
    pdir_out(p);
}

// Disables the led
void led_disable(PIN p)
{
    pdir_in(p);
}

// Toggle the enable/disable state of the led
void led_tobble(PIN p)
{
    pdir_toggle(p);
}

// Turns on the led
void led_on(PIN p)
{
    p_high(p);
}

// Turns off the led
void led_off(PIN p)
{
    p_low(p);
}

// Toggles the state of the led
void led_toggle(PIN p)
{
    p_toggle(p);
}

// Led functions without arguments
// For easy use with function pointers
void redled_enable(void)
{
    led_enable(REDLED);
}

void greenled_enable(void)
{
    led_enable(GREENLED);
}
void redled_disable(void)
{
    led_disable(REDLED);
}

void greenled_disable(void)
{
    led_disable(GREENLED);
}

void redled_tobble(void)
{
    led_tobble(REDLED);
}
void greenled_tobble(void)
{
    led_tobble(GREENLED);
}

void redled_on(void)
{
    led_on(REDLED);
}

void greenled_on(void)
{
    led_on(GREENLED);
}

void redled_off(void)
{
    led_off(REDLED);
}

void greenled_off(void)
{
    led_off(GREENLED);
}

void redled_toggle(void)
{
    led_toggle(REDLED);
}

void greenled_toggle(void)
{
    led_toggle(GREENLED);
}
