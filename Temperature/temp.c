#include "temp.h"

void temp_init(void)
{
    adc_init();
}

int temp_read(void)
{
    tWord t = adc_read();
    // Converts the value to temperature in degrees Celsius. Unknown formula
    // This one gives a degree less than the other one
    //return (unsigned int)( ((t - 673) * 423) / 1024 );
    // Nicer formula
    return (int) ((t * 27069L - 18169625L) >> 16);

}

