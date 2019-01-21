#include "sound.h"

/*
 * Credits to composer Tommy L
 */

/*
 * Beep at the give frequency for the give duration
 */
void beep(unsigned int frequency, unsigned int duration)
{
    int i;
    // Calculate the half-period for frequency
    long delay = (long) (10000 / frequency * 8);
    // Calculate how many times square waves to generate to fill the duration
    long time = (long) ((duration * 3000) / (delay * 2));

    // Generate <time> square waves
    for (i = 0; i < time; i++)
    {
        P1OUT |= SPEAKER;   // Speaker high
        delay_us(delay);    // Wait half-period
        P1OUT &= ~SPEAKER;  // Speaker low
        delay_us(delay);    // Wait half period
    }
    // Small delay to sound better
    delay_ms(NOTEINTERVAL);
}

/*
 * Delay the given amount of milliseconds
 */
void delay_ms(tWord ms)
{
    tWord i;
    for (i = 0; i <= ms; i++)
    {
        __delay_cycles(1000);
    }
}

/*
 * Delay the given amount of microseconds
 */
void delay_us(tWord us)
{
    tWord i;
    for (i = 0; i <= us / 2; i++)
        __delay_cycles(1);
}

/*
 * Intro music
 */
void sound_intro(void)
{
    beep(a, 500);
    beep(a, 500);
    beep(a, 500);
    beep(f, 250);
    beep(cH, 250);
    beep(a, 500);
    beep(f, 250);
    beep(cH, 250);
    beep(a, 1000);
}

/*
 * Winning music
 */
void sound_win(void)
{
    beep(dH, 50);
    beep(dH, 250);
    beep(dH, 250);
    delay_ms(50);
    beep(dH, 50);
    beep(dH, 250);
    beep(dH, 250);
    delay_ms(50);
    beep(eH, 500);
    beep(dH, 250);
    beep(fSH, 1000);
}

/*
 * Loosing sound
 */
void sound_loose(void)
{
    beep(g, 250);
    beep(f, 250);
    beep(e, 250);
    beep(c, 1000);
}

/*
 * Laser sound
 */
void sound_laser(void)
{
    beep(1500, 1);
    beep(1500, 1);
}

/*
 * Alien killed sound
 */
void sound_alienkill(void)
{
    beep(c, 1);
    beep(c, 1);
    beep(c, 1);
    beep(c, 1);
    beep(100, 1000);
}

