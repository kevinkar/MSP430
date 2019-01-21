#include "switch.h"

/*
 * Initialize pin as switch (input)
 */
void switch_init(PIN p)
{
    pdir_in(p); // Set as input.
    p_ren(p);   // Enable resistor.
    p_high(p);  // Set to Pull-up mode (high).
}

/*
 * Initialize switch with interrupts enabled
 */
void switch_initwie(PIN p)
{
    switch_init(p);
    p_ie(p);   // Enable interrupts on pin.
    p_es(p);   // Set edge to high.
    p_cifg(p); // Clear interrupt flag.
}

/*
 * Checks and returns current state of switch
 */
int switch_pressed(PIN p)
{
    // For switch w/ pull-up r enabled.
    // Bit IN when pressed == 0.
    // ~P1IN & PIN3 switch is pressed.
    return ~p_read(p) & p;
}

/*
 * May be called on switch interrupt
 */
void switch_action(void)
{
    timer_stopie();
    timer_resetcounter();
    game_input();
    switchflag = 0;
    timer_startie();
}

/*
 * ISR for switch interrupt
 */
void __attribute__((interrupt(PORT1_VECTOR))) PORT1_ISR(void)
{
    //Stores the switch action in the switchflag variable
    switchflag |= P1IFG;
    switch_action();

    // Clears interrupt flag.
    P1IFG &= 0;

    if (firstrun)
    {
        firstrun = 0;
        __bic_SR_register_on_exit(LPM4_bits + GIE);
    }
}
