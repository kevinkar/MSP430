# Synchronized traffic lights

A timer based task scheduler is used to operate a master traffic light which controls a slave light. In case the communication link is cut, the master returns to init and tries to re-establish communication. The lights uses the built-in LED's on the boards.

## Known problems:

- The slave light does not have a watchdog so it stays in the last mode if communcation is broken.

## Includes Code Composer Studio project files

### To run:

- For the slave light, put a jumper over pins P1.4 and P1.5.
- Put the UART jumpers to HW mode and connect the two MSP430G2's UART by crossing TX and RX with jumper wires.
- Connect GND between the two boards. This will power the second board from the first.
