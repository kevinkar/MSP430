/*
 * Maximum timer delay is 524ms.
 *
 */

#include <main.h>

static int newtemperature;
static int temperature;
static int temperaturechanged;
static int interval;
static char temperaturestring[BUFFER_SIZE];
static int switchflag;

void main(void)
{
    // Our system level init
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
    // System runs at 1 Mhz. Remember to adjust for baud rate in UART
    //Check calibration constants
    if (CALBC1_1MHZ == 0xFF || CALDCO_1MHZ == 0xFF)
    {
        //Trap the CPU in an infinite loop
        while (1)
            ;
    }

    DCOCTL = 0;
    BCSCTL1 = CALBC1_1MHZ;  // 1Mhz calibration data
    DCOCTL = CALDCO_1MHZ;   // 1Mhz calibration data
    //BCSCTL2 &= ~(DIVS_3);   // Divider for SMCLK = DCO = 1MHz

    port_reset();          // Terminates/Initializes all ports
    // Base system is now ready for use
    // Scheduler requires timer to be active
    timer_init();
    scheduler_init();
    switch_init(SW1);
    temp_init();

    newtemperature = 0;
    temperature = 0;
    temperaturechanged = 0;
    interval = 0;

    UART_Init();
    redled_enable();
    greenled_enable();
    // Enables interrupts on system, and low-power mode 1
    // CPU OFF, Clock Gen 0 OFF
    __bis_SR_register(LPM1_bits + GIE);

    //TXByte = (unsigned char)( ((tempAverage - 630) * 761) / 1024 );

    while (TRUE)
    { // Loop till the end of time
      //scheduler_dispatch();
      //__bis_SR_register(LPM1_bits + GIE);
      // Sleeps until interrupted
    }
}

// Timer interrupt calls this function
void timer_action(void)
{
    scheduler_dispatch();
}

// Switch interrupt calls this function
void switch_action(void)
{
    // Does nothing in this version
}

void check_switch(void)
{
    // Toggle LED state on buttonpress
    // Uses timed debounce
    if (switch_pressed(SW1))
    {
        if (switchflag)
        {
            switchflag = 0;
            led_tobble(REDLED);
            led_tobble(GREENLED);
        }
        else
        {
            // Used for debouncing the switch
            switchflag = 1;
        }
    }
}

void check_temperature(void)
{
    newtemperature = (int) temp_read();

    // If the new temperature differs from the old
    if (newtemperature != temperature)
    {
        temperaturechanged = 1;
        temperature = newtemperature;
    }
    else
    {
        temperaturechanged = 0;
    }
}

void prepare_temperature(void)
{
    // Temperature has changed, need to get a string
    if (temperaturechanged)
    {
        // Since numbers are sequential in ASCII
        // We can just add '48' which gives us a start from 0
        //char hundreds = ((int) t/100)+48;
        char tens = ((int) temperature / 10) + 48;
        char ones = ((int) temperature % 10) + 48;
        temperaturestring[0] = tens;
        temperaturestring[1] = ones;
    }
}

void send_temperature(void)
{
    UART_Write(temperaturestring);
}

void send_newline(void)
{
    UART_Write(NL);
}

// TODO Another option would be to create a state machine for this
void blink_temperature(void)
{
    // Temperature has changed
    if (temperaturechanged)
    {
        // Calculates a suitable interval for blinking
        // In this case, 2 degrees equals 1 Hertz
        interval = 2000 / (temperature * 125);
        // Resets the LEDs to sync them
        led_off(REDLED);
        led_off(GREENLED);
    }

    if (temperature > TEMPERATURE_TRESHOLD)
    {
        led_off(GREENLED);
        led_toggle(REDLED);

    }
    else if (temperature < TEMPERATURE_TRESHOLD)
    {
        led_off(REDLED);
        led_toggle(GREENLED);

    }
    else
    {
        led_toggle(REDLED);
        led_toggle(GREENLED);
    }

    // Task adding a task means we need a list overhead of one task
    scheduler_add(&blink_temperature, interval, 0);

}

