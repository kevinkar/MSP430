#ifndef ALIEN_H
#define ALIEN_H

#include "main.h"

/*
 * ALIEN (Switch) definitions
 */
#define LEFT PIN3
#define RIGHT PIN4
#define SHOOT PIN5

/*
 * The screen are "pixel" dots as binary
 */
#define DOT0  0b1000000000000000
#define DOT1  0b0100000000000000
#define DOT2  0b0010000000000000
#define DOT3  0b0001000000000000
#define DOT4  0b0000100000000000
#define DOT5  0b0000010000000000
#define DOT6  0b0000001000000000
#define DOT7  0b0000000100000000
#define DOT8  0b0000000010000000
#define DOT9  0b0000000001000000
#define DOT10 0b0000000000100000
#define DOT11 0b0000000000010000
#define DOT12 0b0000000000001000
#define DOT13 0b0000000000000100
#define DOT14 0b0000000000000010
#define DOT15 0b0000000000000001

/*
 * Craft image
 */
#define CRAFTTOP (DOT2)
#define CRAFTMIDDLE (DOT1 | DOT2 | DOT3)
#define CRAFTBOTTOM (DOT0 | DOT1 | DOT2 | DOT3 | DOT4)

/*
 * Alien image
 */
#define ALIENTOP (DOT0 | DOT1 | DOT2)
#define ALIENBOTTOM (DOT0 | DOT2)

/*
 * Game area, 16x16 pixels
 */
#define ROWS 16
#define COLUMNS 16 // Depending on system, size of int

/*
 * Array sizes for different elements
 */
#define ALIEN_SIZE ROWS
#define CRAFT_SIZE 2
#define HIT_SIZE (ROWS - CRAFT_SIZE)
#define LASER_SIZE (ROWS - CRAFT_SIZE)

/*
 * How many aliens do we want
 * Not safe
 */
#define ALIENROWS 2
#define ALIENSPERROW 3

/*
 * UART printing helpers
 */
#define ROWSIZE COLUMNS+3   // Width of printed row
#define CPIPE 124           // Char value for pipe
#define CFILL 35            // Char value for filling character, hash
#define CBLANK 32           // Char value for whitespace
static char *NL = "\r\n";
static char *LINE = "__________________";

/*
 * Initialize the game venue
 */
void game_init(void);

/*
 * Start a new game
 */
void game_start(void);

/*
 * Called upon death to offer new game
 */
void game_over(void);

/*
 * Called upon winning to congratulate and offer new game
 */
void game_won(void);

/*
 * Called when an input switch has been actuated to process that
 */
void game_input(void);

/*
 * Checks and updates game logic
 */
void game_action(void);

/*
 * Output the game area over UART
 */
void draw(void);
/*
 * Generates the character array responding to the game row given
 */
void generate_row(tWord rowin, char* rowout);
/*
 * Resets a given char array of given size
 */
void chararray_reset(char *arr, tWord size);

/*
 * Empties a tWord array of given size
 */
void array_reset(tWord *arr, tWord size);

/*
 * Initialize the aliens
 */
void alien_init(void);
/*
 * Initialize the craft
 */
void craft_init(void);

/*
 * Initialize the hit area (as empty)
 */
void hit_init(void);
/*
 * Initialize the laser area (as empty)
 */
void laser_init(void);

/*
 * Alien advances one row downwards
 */
void alien_update(void);

/*
 * Alien sideways twerk
 */
void alien_twerk(void);
/*
 * Laser shots advance one row upwards
 */
void laser_update(void);

/*
 * Moves the craft a step to the right
 */
void craft_rightstep(void);
/*
 * Moves the craft a step to the left
 */
void craft_leftstep(void);
/*
 * Spawns a new laser
 */
void laser_shoot(void);

/*
 * Checks if any aliens have been hit and eliminates them
 */
void alien_hit(void);

/*
 * Checks if there are aliens left, and returns >0 if there are aliens left
 */
tWord aliens_left(void);

#endif
