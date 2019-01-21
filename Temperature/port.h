#ifndef PORT_H
#define PORT_H

#include "main.h"

/*
 * Outlines functions for all registry operations on PORT1
 *
 */

// Initializes and terminates all ports (1,2,3) and all pins
void port_reset();

void pdir_out(PIN p);

void pdir_in(PIN p);

void pdir_toggle(PIN p);

void p_high(PIN p);

void p_low(PIN p);

void p_toggle(PIN p);

void p_clrin(PIN p);

void p_ren(PIN p);

void p_rdi(PIN p);

void p_ie(PIN p);

void p_id(PIN p);

void p_ifg(PIN p);

void p_cifg(PIN p);

void p_es(PIN p);

void p_ds(PIN p);

int p_read(PIN p);

#endif
