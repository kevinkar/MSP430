#include "main.h"

void main(void)
{
    /*
     * Prepare base system for use
     */
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    DCOCTL = 0;                 // Select lowest DCOx and MODx settings.
    BCSCTL1 = CALBC1_1MHZ;      // 1Mhz calibration data.
    DCOCTL = CALDCO_1MHZ;       // 1Mhz calibration data.
    BCSCTL2 = 0;                // SMCLK = DCO
    port_reset();               // Terminates/Initializes all ports.

    /*
     * Set up the switches for game input with interrupts
     */
    switch_initwie(LEFT);   // P1.3 for left step
    switch_initwie(RIGHT);  // P1.4 for right step
    switch_initwie(SHOOT);  // P1.5 for shoot

    uart_init();        // Fires up the UART communications for use.
    timer_init();       // Initialize the timer
    switchflag = 0;     // Used for forwarding/storing input switch values
    firstrun = 1;       // First time so we know to wait for game start

    // Setup the game
    game_init();
    // Wait for first input interrupt
    __bis_SR_register(LPM1_bits + GIE);
    game_start();
    timer_startie();
    while (TRUE)
    { // Loop till the end of time
        // Waits for timer to resume from sleep
        __bis_SR_register(LPM1_bits + GIE);
        timer_stopie();
        timer_resetcounter();
        game_action();
        timer_startie();
    }
}

/*
 * Restart the whole thing for a new game
 */
void restart(void)
{
    // Writes to the WD register without password, causes reset.
    // DEAD is just some embedded humor, pun intended.
    WDTCTL = 0xDEAD;
}

