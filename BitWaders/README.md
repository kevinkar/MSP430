# MSP430 UART ASCII SPACE INVADERS

# What is this?

This project is a Space Invaders-inspired small game (16x8-bit = 128 bit bitmap display). It runs on the Texas Instruments MSP430G2553 board. The board is not ideal for this kind of application and the game idea not very useful in itself. Rather, the idea is to demonstrate different aspects of embdedded systems development and programming. Watchdog, UART, button debouncing, registry configuration, low-power aspects such as sleep mode, square wave sound generation, timers, pointers and binary arithmetics.


# Known bugs

1. Debouncing is a bit too sensitive and does not work properly.

2. The laser shots are not removed immediately.

3. UART communication is limited to 9600 baud which seriously limits the output refresh rate.

# Continuation

- Instead of displaying the screen over UART, it could use a LED matrix display, improving on bug 3.

- The screen area could be extended beyond 16x8-bit

- Improve on gameplay to make the game more advanced and fun.

## Includes Code Composer Studio project files

### To run:

- Verify Project > Properties that heap size is increased to 220 (default: 80)

- Verify that MSP430 UART is set to SW mode

- Connect buttons and speaker. Buttons are pulled-up (high). Connect other end to ground.
    - P1.3 = LEFT
    - P1.4 = RIGHT
    - P1.5 = SHOOT
    - P1.6 = SPEAKER

- Start serial monitor with baud 9600. Recommended 19 lines to get a nice screen. 

#### MSP430 USBSERIAL IS LIMITED TO 9600 baud.
