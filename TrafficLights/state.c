#include "state.h"

// Initializes traffic lights for use
void tlight_init()
{

    current_state = AMBER; // Sets us in the starting state
    timer_ticks = 0;
    awaiting_ack = 0;
    received_ack = 0;
    led_off(REDLED);
    led_off(GREENLED);
    tlight_update();
}

void tlight_master()
{

    if (awaiting_ack)
    { // We are awaiting an ack.
        received_ack = uart_readbyte();
        //uart_readbyte();
        if (received_ack)
        { // We have received an ack.
            if (received_ack == awaiting_ack)
            {    // The ack was not what we expected
                awaiting_ack = 0;
                received_ack = 0;
            }
            else
            {
                tlight_init();
            }
        }
        else
        {
            tlight_init();
        }
    }

    switch (current_state)
    {
    case AMBER:
    {
        if (timer_ticks > AMBER_DURATION)
        {
            timer_ticks = 0;
            current_state = RED;
            awaiting_ack = ACK_GREEN;
            uart_sendbyte(GOTO_GREEN);
        }
        break;
    }
    case RED:
    {
        if (timer_ticks > RED_DURATION)
        {
            timer_ticks = 0;
            current_state = REDGREEN;
            awaiting_ack = ACK_GREENRED;
            uart_sendbyte(GOTO_GREENRED);
        }
        break;
    }
    case GREEN:
    {
        if (timer_ticks > GREEN_DURATION)
        {
            timer_ticks = 0;
            current_state = GREENRED;
            awaiting_ack = ACK_REDGREEN;
            uart_sendbyte(GOTO_REDGREEN);
        }
        break;
    }
    case REDGREEN:
    {
        if (timer_ticks > REDGREEN_DURATION)
        {
            timer_ticks = 0;
            current_state = GREEN;
            awaiting_ack = ACK_RED;
            uart_sendbyte(GOTO_RED);
        }
        break;
    }
    case GREENRED:
    {
        if (timer_ticks > GREENRED_DURATION)
        {
            timer_ticks = 0;
            current_state = RED;
            awaiting_ack = ACK_GREEN;
            uart_sendbyte(GOTO_GREEN);
        }
        break;
    }
    }
    timer_ticks++; // Increment the timer ticks counter
    tlight_update();
}

void tlight_slave()
{
    led_toggle(GREENLED);
    received_message = uart_readbyte();
    //uart_readbyte();

    switch (received_message)
    {
    case GOTO_AMBER:
    {
        current_state = AMBER;
        uart_sendbyte(ACK_AMBER);
        break;
    }
    case GOTO_RED:
    {
        current_state = RED;
        uart_sendbyte(ACK_RED);
        break;
    }
    case GOTO_GREEN:
    {
        current_state = GREEN;
        uart_sendbyte(ACK_GREEN);
        break;
    }
    case GOTO_REDGREEN:
    {
        current_state = REDGREEN;
        uart_sendbyte(ACK_REDGREEN);
        break;
    }
    case GOTO_GREENRED:
    {
        current_state = GREENRED;
        uart_sendbyte(ACK_GREENRED);
        break;
    }
    default:
    {
        // TODO Error handling and behaviour
        uart_sendbyte(ACK_ERROR_0);
        tlight_init();
        break;
    }
    }
    tlight_update();
}

void tlight_update()
{

    switch (current_state)
    {
    case AMBER:
    {
        p_ren(REDLED); // Resistor is used to light the red led as amber
        led_on(REDLED);
        led_off(GREENLED);
        break;
    }
    case RED:
    {
        p_rdi(REDLED);
        led_on(REDLED);
        led_off(GREENLED);
        break;
    }
    case GREEN:
    {
        p_rdi(REDLED);
        led_off(REDLED);
        led_on(GREENLED);
        break;
    }
    case REDGREEN:
    {
        p_rdi(REDLED);
        led_on(REDLED);
        led_on(GREENLED);
        break;
    }
    case GREENRED:
    {
        p_rdi(REDLED);
        led_on(REDLED);
        led_on(GREENLED);
        break;
    }
    }
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
        uart_sendbyte(GOTO_GREENRED);
    }
}
