#include "timer.h"

/*
 * Initialize timer with delay given here
 */
void timer_init(void)
{
    TA0CTL = TASSEL_2 + MC_1 + ID_3; // Timer Control settings TA0CTL.
    TA0CCR0 = TIMER_DELAY;           // Timer value to count to TACCR0.
}

void timer_startie(void)
{
    TA0CCTL0 = CCIE;                 // Enable Timer A interrupt.
}

/*
 * Stop the timer interrupts
 */
void timer_stopie(void)
{
    TA0CCTL0 &= ~CCIE;
}

/*
 * Reset the timer counter register
 */
void timer_resetcounter(void)
{
    TA0R = 0;
}

/*
 * May be called on timer interrupt
 */
void timer_action(void)
{

}

/*
 * ISR for timer interrupt
 */
void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)
{
    __bic_SR_register_on_exit(LPM4_bits + GIE); // Clears all possible LPMs
}

/* Timer Control settings as below:*/
/* Timer A clock source select: TASSEL_0 - TACLK */
/* Timer A clock source select: TASSEL_1 - ACLK  */
/* Timer A clock source select: TASSEL_2 - SMCLK */
/* Timer A clock source select: TASSEL_3 - INCLK */
/* Timer A mode control: MC_0 - Stop */
/* Timer A mode control: MC_1 - Up to CCR0 */
/* Timer A mode control: MC_2 - Continuous up */
/* Timer A mode control: MC_3 - Up/Down */
/* Timer A input divider: ID_0 - /1 */
/* Timer A input divider: ID_1 - /2 */
/* Timer A input divider: ID_2 - /4 */
/* Timer A input divider: ID_3 - /8 */
