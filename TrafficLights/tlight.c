/*
 * Synchronized traffic lights
 *
 */

#include "tlight.h"

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    DCOCTL = 0;               // Select lowest DCOx and MODx settings.
    BCSCTL1 = CALBC1_1MHZ;    // 1Mhz calibration data.
    DCOCTL = CALDCO_1MHZ;     // 1Mhz calibration data.
    BCSCTL2 = 0;              // SMCLK = DCO
    port_reset();             // Terminates/Initializes all ports.

    // Base system is now ready for use

    tlight_init();
    led_enable(REDLED);   // Enables the red LED.
    led_enable(GREENLED); // Enables the green LED.

    switch_initwie(SW1); // Enables the switch for use.
    uart_init();         // Fires up the UART communications for use.

    pdir_in(PIN5); // Set as input.
    p_ren(PIN5);   // Enable resistor.
    p_low(PIN5);   // Set to Pull-down mode (high).

    pdir_out(PIN4);
    p_high(PIN4);

    if (P1IN & PIN5)
    {
        gopmode = SLAVE;
        slave_init();
    }
    else
    {
        gopmode = MASTER;
        master_init();
    }

    while (TRUE)
    { // Loop till the end of time
        __bis_SR_register(LPM1_bits + GIE); // Goes into LPM1 with interrupts enabled
        if (gopmode == SLAVE)
        {
            scheduler_dispatch();
        }
    }
}

void master_init(void)
{
    // The scheduler tasks the master is supposed to have.
    scheduler_add(&tlight_master, 0, 500);
    timer_init();     // Scheduler requires timer to be active.
}

void slave_init(void)
{
    // The scheduler tasks the slave is supposed to have.
    scheduler_add(&tlight_slave, 0, 500);
    // Here the watchdog would be configured
}

// Timer interrupt calls this function
void timer_action(void)
{
    scheduler_dispatch();
}

// Switch interrupt calls this function
void switch_action(void)
{
    led_tobble(REDLED);
    led_tobble(GREENLED);
}

void send_newline(void)
{
    __bis_SR_register(GIE); // UART needs interrupts
    uart_write(NL);         // Send newline
}
