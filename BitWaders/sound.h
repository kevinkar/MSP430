#ifndef SOUND_H
#define SOUND_H

#include "main.h"

/*
 * SPEAKER definitions
 */
#define SPEAKER PIN6
#define NOTEINTERVAL 20

/*
 * Note frequencies in Hertz
 */
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 466
#define b 494
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

/*
 * Beep at the give frequency for the give duration
 */
void beep(tWord frequency, tWord duration);

/*
 * Delay the given amount of milliseconds
 */
void delay_ms(tWord ms);

/*
 * Delay the given amount of microseconds
 */
void delay_us(tWord us);

/*
 * Intro music
 */
void sound_intro(void);

/*
 * Winning music
 */
void sound_win(void);

/*
 * Loosing sound
 */
void sound_loose(void);

/*
 * Laser sound
 */
void sound_laser(void);

/*
 * Alien killed sound
 */
void sound_alienkill(void);

#endif
