#include "alien.h"

/*
 * Game element array pointers
 */
tWord *alien;
tWord *craft;
tWord *hit;
tWord *laser;

/*
 * Original value of pointers, for resetting
 */
tWord *alienreset;
tWord *craftreset;
tWord *hitreset;
tWord *laserreset;

/*
 * Center of craft
 */
tWord craftcenter;

/*
 * Game logic counters
 */
tWord twerk;
tWord timerstep;
tWord inputstep;

/*
 * Checks if aliens have collided with the earth
 */
#define EARTHCOLLISION (alien[ALIEN_SIZE - 1]>0)
/*
 * Checks if aliens have collided with the craft
 */
#define CRAFTCOLLISION (((craft[0] & alien[ALIEN_SIZE - 2])| (craft[1] & alien[ALIEN_SIZE - 1]))>0)

/*
 * Initialize the game
 */
void game_init(void)
{
    // Malloc the arrays
    alien = malloc(sizeof(int) * ALIEN_SIZE);
    craft = malloc(sizeof(int) * CRAFT_SIZE);
    hit = malloc(sizeof(int) * HIT_SIZE);
    laser = malloc(sizeof(int) * LASER_SIZE);
    uart_write("Press the any key to start this awesome game.\r\n");
    // To start a game next, call game_start()
}

/*
 * Start a new game
 */
void game_start(void)
{
    // Empty the arrays, set up reset pointers and initial image
    alien_init();
    craft_init();
    hit_init();
    laser_init();
    // Resets game variables
    twerk = 0;
    timerstep = 0;
    inputstep = 0;
    switchflag = 0;

    sound_intro();
}

/*
 * Called upon failure to offer new game
 */
void game_over(void)
{
    TA0CCTL0 = 0;
    uart_write("GAME OVER.\r\n");
    uart_write(NL);
    sound_loose();
    restart();
}

/*
 * Called upon winning to congratulate and offer new game
 */
void game_won(void)
{
    TA0CCTL0 = 0;
    uart_write("GAME WON.\r\n");
    uart_write(NL);
    sound_win();
    restart();
}

/*
 * Called when an input switch has been actuated to process that
 */
void game_input(void)
{
    // Uses the global switchflag
    inputstep++;
    if (switchflag & LEFT)
    { //Left
        beep(150, 100);
        craft_leftstep();
    }
    else if (switchflag & RIGHT)
    { // Right
        beep(150, 100);
        craft_rightstep();

    }
    else if (switchflag & SHOOT)
    { //Shoot
        sound_laser();
        laser_shoot();
    }
    // Also update game logic at this point
    game_action();
}

/*
 * Checks and updates game logic
 */
void game_action(void)
{
    timerstep++;
    if (timerstep >= 3)
    {   //
        timerstep = 0;
        if (inputstep >= 3)
        {
            inputstep = 0;
            alien_update();
        }
        laser_update();
        alien_twerk();
        alien_hit();
        draw();
        if (EARTHCOLLISION || CRAFTCOLLISION)
        {
            game_over();
        }
        else if (!aliens_left())
        {
            game_won();
        }
    }
}

/*
 * Output the game area over UART
 */
void draw(void)
{
    uart_write(NL);
    tWord i;
    tWord total = 0;
    char row[20];
    uart_write(LINE);
    uart_write(NL);

    for (i = 0; i < LASER_SIZE; i++) // or HIT_SIZE, same thing
    {
        chararray_reset(row, ROWSIZE);
        total = alien[i] | hit[i] | laser[i];
        generate_row(total, row);
        uart_write(row);
        uart_write(NL);
    }
    chararray_reset(row, ROWSIZE);
    total = alien[i++] | craft[0];
    generate_row(total, row);
    uart_write(row);
    uart_write(NL);

    chararray_reset(row, ROWSIZE);
    total = alien[i++] | craft[1];
    generate_row(total, row);
    uart_write(row);
    uart_write(NL);

    uart_write(LINE);
    uart_write(NL);
}

/*
 * Generates the character array responding to the game row given
 */
void generate_row(tWord rowin, char* rowout)
{
    tWord x = 0;
    tWord dotpoint = DOT0;
    rowout[x] = CPIPE;    // Print line start
    while (x <= COLUMNS)
    {   // Go through every column in the row
        if (rowin & (dotpoint >> x++))
        {   // Current dot should be drawn
            rowout[x] = CFILL;
        }
        else
        {   // Send blank
            rowout[x] = CBLANK;
        }
    }
    rowout[x++] = CPIPE; // Print line ending
}

/*
 * Resets a given char array of given size
 */
void chararray_reset(char *arr, tWord size)
{
    tWord i = size;
    while (i > 0)
    {
        *arr++ = 0;
        i--;
    }
}

/*
 * Empties a tWord array of given size
 */
void array_reset(tWord *arr, tWord size)
{
    tWord i = size;
    while (i > 0)
    {
        *arr++ = 0;
        i--;
    }
}

/*
 * Initialize the aliens
 */
void alien_init(void)
{
    array_reset(alien, ALIEN_SIZE);
    alienreset = alien;
    tWord i = 0;
    tWord y = 0;
    tWord rowoffset = 1;
    for (i = 0; i < ALIENROWS; i++)
    {
        for (y = rowoffset; y < COLUMNS - rowoffset;
                y += (COLUMNS / ALIENSPERROW))
        {
            *alien |= (ALIENTOP >> y);
        }
        *alien++;
        for (y = rowoffset; y < COLUMNS - rowoffset;
                y += (COLUMNS / ALIENSPERROW))
        {
            *alien |= (ALIENBOTTOM >> y);
        }
        *alien++;
        *alien++;

        if (rowoffset++)
        {
            rowoffset = 0;
        }
        else
        {
            rowoffset++;
        }
    }
    alien = alienreset;
}

/*
 * Initialize the craft
 */
void craft_init(void)
{
    array_reset(craft, CRAFT_SIZE);
    craftreset = craft;
    tWord craftoffset = 0;
    craftcenter = DOT2;
    craftoffset = (COLUMNS / 2) - 3; // Center craft
    craftcenter >>= craftoffset;
    *craft++ = CRAFTMIDDLE >> craftoffset;
    *craft++ = CRAFTBOTTOM >> craftoffset;
    craft = craftreset;
}

/*
 * Initialize the hit area (as empty)
 */
void hit_init(void)
{
    array_reset(hit, HIT_SIZE);
    hitreset = hit;
}

/*
 * Initialize the laser area (as empty)
 */
void laser_init(void)
{
    array_reset(laser, LASER_SIZE);
    laserreset = laser;
}

/*
 * Alien advances one row downwards
 */
void alien_update(void)
{
    tWord i;
    for (i = ALIEN_SIZE - 1; i > 0; i--) //for (i = size; i-- > 0;)
    {
        alien[i] = (alien[i - 1]);
    }
    alien[i] = 0; // Empty the last row.
}

/*
 * Alien sideways twerk
 */
void alien_twerk(void)
{
    tWord i;
    for (i = 0; i < ALIEN_SIZE; i++)
    {
        if (twerk)
        {
            alien[i] <<= 1;
        }
        else
        {
            alien[i] >>= 1;
        }
    }
    if (twerk++)
    {
        twerk = 0;
    }
}

/*
 * Laser shots advance one row upwards
 */
void laser_update(void)
{
    tWord i;
    for (i = 0; i < LASER_SIZE - 1; i++)
    {
        laser[i] = laser[i + 1];
    }
    laser[i] = 0; // Empty the last row.
}

/*
 * Moves the craft a step to the right
 */
void craft_rightstep(void)
{
    if (!(craft[1] & DOT15))
    { // Checks if the craft is at edge
        craft[0] = craft[0] >> 1; //CRAFTMIDDLE >> craftoffset;
        craft[1] = craft[1] >> 1; //CRAFTBOTTOM >> craftoffset;
        craftcenter >>= 1;        //DOT1 >> craftoffset;
    }
}

/*
 * Moves the craft a step to the left
 */
void craft_leftstep(void)
{
    if (!(craft[1] & DOT0))
    {   // Checks if the craft is at edge
        craft[0] = craft[0] << 1; //CRAFTMIDDLE >> craftoffset;
        craft[1] = craft[1] << 1; //CRAFTBOTTOM >> craftoffset;
        craftcenter <<= 1;        //DOT1 >> craftoffset;
    }
}

/*
 * Spawns a new laser
 */
void laser_shoot(void)
{
    laser[LASER_SIZE - 1] |= craftcenter;
}

/*
 * Checks if any aliens have been hit and eliminates them
 */
void alien_hit(void)
{
    array_reset(hit, HIT_SIZE);
    tWord i = 0;
    while (i < HIT_SIZE)
    { // Iterate the laser rows
        *hit++ = (*alien++) & (*laser++); // AND we have a hit
        i++;
    }
    i = 0;
    alien = alienreset;
    hit = hitreset;
    laser = laserreset;

    tWord shot;     // Variable holds the place where we hit an alien.
    tWord compshot; // Temporary, used for comparison
    while (i < HIT_SIZE)
    { // Goes through the whole hit area
        shot = 0;
        compshot = 0;
        if ((shot = hit[i]))
        {   // There was a hit on this row
            alien[i] &= ~shot; // Makes a hole in the alien at the point of impact.
            /*
             * The cases described below are the different points where an alien can be hit.
             * Removes the alien from the area
             */
            if ((compshot = alien[i - 1]) & shot)
            {   // Case 2 or 3, hit one of the forward "legs"
                if (compshot & shot >> 1)
                {   // Reset Case 2
                    alien[i - 1] &= ~shot;
                    shot >>= 1;
                    alien[i - 1] &= ~shot;
                    shot >>= 1;
                    alien[i - 1] &= ~shot;
                    alien[i] &= ~shot;
                    shot <<= 2;
                }
                else if (compshot & shot << 1)
                {   // Reset Case 3
                    alien[i - 1] &= ~shot;
                    shot <<= 1;
                    alien[i - 1] &= ~shot;
                    shot <<= 1;
                    alien[i - 1] &= ~shot;
                    alien[i] &= ~shot;
                    shot >>= 2;
                }
            }
            else if (alien[i] & shot >> 1)
            {   // Case 1 or 4, something to the right
                if (alien[i] & shot << 1)
                {   // Reset Case 1, something to the left
                    shot <<= 1;
                    alien[i] &= ~shot;
                    alien[i + 1] &= ~shot;
                    shot >>= 2;
                    alien[i] &= ~shot;
                    alien[i + 1] &= ~shot;
                    shot <<= 1;
                }
                else
                {   // Reset Case 4, nothing to the left
                    alien[i + 1] &= ~shot;
                    shot >>= 1;
                    alien[i] &= ~shot;
                    shot >>= 1;
                    alien[i] &= ~shot;
                    alien[i + 1] &= ~shot;
                    shot <<= 2;
                }
            }
            else if (alien[i] & shot << 1)
            {   // Reset Case 5, something to the left
                alien[i + 1] &= ~shot;
                shot <<= 1;
                alien[i] &= ~shot;
                shot <<= 1;
                alien[i] &= ~shot;
                alien[i + 1] &= ~shot;
                shot >>= 2;
            }
            // Remove the laser that hit. There are some problems with this
            // The laser is not removed until next game_action()...
            laser[i] &= ~shot;  // Removes the laser that hit
            // An alien has been hit and eliminated
            // Actually plays for every hit, not per alien
            sound_alienkill();
        }
        i++;
    }
}

/*
 * Checks if there are aliens left, and returns >0 if there are aliens left
 */
tWord aliens_left(void)
{
    tWord i = 0;
    tWord aliensleft = 0;
    while (i++ < ALIEN_SIZE)
    {
        aliensleft |= (*alien++);
    }
    alien = alienreset;
    return aliensleft;
}
