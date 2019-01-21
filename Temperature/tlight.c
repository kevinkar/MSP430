#include "tlight.h"

// Initializes traffic lights for use
void tlight_init()
{
    // Main.c needs to initialize suitable timer
    switch_initwie(SW1);        // Initializes SW1 (PIN3) as an interrupt switch
    led_enable(REDLED);         // Enables LED1 (PIN0) (as output)
    led_enable(GREENLED);       // Enables LED2 (PIN6) (as output)
    current_state = AMBER;      // Sets us in the starting state
    timer_ticks = 0;            // Resets the tick counter
    UART_Write(AMBER_TEXT);     // Prints that we are in AMBER state
}

// State machine counts timer ticks
void tlight_update()
{
    /*
     * Switch used for states. Logic is to repeatedly activate the state we want
     * and when the timer duration is achieved, we set to the next state
     * and UART the state we have entered.
     * Increment ticker after each function call, reset on state change
     * Compares with > larger than.
     * This since we always increase, even on state change, and if we get
     * some interrupt problems causing skipped counts, we are prepared
     */

    switch (current_state)
    {
    case AMBER:
    {
        p_ren(REDLED);         // Resistor is used to light the red led as amber
        led_on(REDLED);
        led_off(GREENLED);
        if (timer_ticks > AMBER_DURATION)
        {
            timer_ticks = 0;
            current_state = RED;
            UART_Write(RED_TEXT);
        }
        break;
    }
    case RED:
    {
        p_rdi(REDLED);
        led_on(REDLED);
        led_off(GREENLED);
        if (timer_ticks > RED_DURATION)
        {
            timer_ticks = 0;
            current_state = REDGREEN;
            UART_Write(REDGREEN_TEXT);
        }
        break;
    }
    case GREEN:
    {
        led_off(REDLED);
        led_on(GREENLED);
        if (timer_ticks > GREEN_DURATION)
        {
            timer_ticks = 0;
            current_state = GREENRED;
            UART_Write(GREENRED_TEXT);
        }
        break;
    }
    case REDGREEN:
    {
        led_on(REDLED);
        led_on(GREENLED);
        if (timer_ticks > REDGREEN_DURATION)
        {
            timer_ticks = 0;
            current_state = GREEN;
            UART_Write(GREEN_TEXT);
        }
        break;
    }
    case GREENRED:
    {
        led_on(REDLED);
        led_on(GREENLED);
        if (timer_ticks > GREENRED_DURATION)
        {
            timer_ticks = 0;
            current_state = RED;
            UART_Write(RED_TEXT);
        }
        break;
    }
    }
    timer_ticks++;              // Increment the timer ticks counter
}

// Go from red to green(thru red+green)
// Called on switch actuation
void tlight_override()
{
    // Only works from red state
    if (current_state == RED)
    {
        led_on(REDLED);
        led_on(GREENLED);
        current_state = REDGREEN;
        timer_ticks = 0;
        UART_Write(RED_OVERRIDE);
    }
}
