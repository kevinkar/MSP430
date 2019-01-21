/*
 *
 *
 */

#include "port.h"

void port_reset()
{
    P1DIR |= 0xFF;
    P1OUT &= 0x00;

    P2DIR |= 0xFF;
    P2OUT &= 0x00;

    P3DIR |= 0xFF;
    P3OUT &= 0x00;
}

void pdir_out(PIN p)
{
    P1DIR |= p;
}

void pdir_in(PIN p)
{
    P1DIR &= ~p;
}

void pdir_toggle(PIN p)
{
    P1DIR ^= p;
}

void p_high(PIN p)
{
    P1OUT |= p;
}

void p_low(PIN p)
{
    P1OUT &= ~p;
}

void p_toggle(PIN p)
{
    P1OUT ^= p;
}

void p_ren(PIN p)
{
    P1REN |= p;
}

void p_rdi(PIN p)
{
    P1REN &= ~p;
}

void p_ie(PIN p)
{
    P1IE |= p;
}

void p_id(PIN p)
{
    P1IE &= ~p;
}

void p_ifg(PIN p)
{
    P1IFG |= p;
}

void p_cifg(PIN p)
{
    P1IFG &= ~p;
}

void p_es(PIN p)
{
    P1IES |= p;
}

void p_ds(PIN p)
{
    P1IES &= ~p;
}

int p_read(PIN p)
{
    return (P1IN & p);
}

// To enable UART serial communication, set pins SEL and SEL2.
void p_uart(PIN p)
{
    P1SEL |= p;
    P1SEL2 |= p;
}

/* For reference
 PORT 1 REGISTER WORDS
 Port P1 selection 2 P1SEL2 041h
 Port P1 resistor enable P1REN 027h
 Port P1 selection P1SEL 026h
 Port P1 interrupt enable P1IE 025h
 Port P1 interrupt edge select P1IES 024h
 Port P1 interrupt flag P1IFG 023h
 Port P1 direction P1DIR 022h
 Port P1 output P1OUT 021h
 Port P1 input P1IN 020h
 */
