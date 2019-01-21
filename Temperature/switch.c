#include "switch.h"

// Initializes pin as switch (input)
void switch_init(PIN p)
{
    pdir_in(p);  // Set as input
    p_ren(p);    // Enable resistor
    p_high(p);   // Set to Pull-up mode (high)
}

// Initializes switch with interrupts enabled
void switch_initwie(PIN p)
{
    switch_init(p);
    p_ie(p);     // Enable interrupts on pin
    p_es(p);     // Set edge to high
    p_cifg(p);   // Clear interrupt flag
}

// Checks current state of switch
int switch_pressed(PIN p)
{
    // For switch w/ pull-up r enabled
    // Bit IN when pressed == 0
    // ~P1IN & PIN3 switch is pressed
    return ~p_read(p) & p;
}

// Runs on switch actuation interrupt
void __attribute__((interrupt(PORT1_VECTOR))) PORT1_ISR(void)
{
    switch_action();
    // Clears interrupt flag
    p_cifg(PIN3);
    // Clears CPUOFF bit, enabling CPU again
    //__bic_SR_register_on_exit(LPM0_bits);
}
