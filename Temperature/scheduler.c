#include "scheduler.h"

// Add the tasks we are supposed to run to the scheduler
void scheduler_init(void)
{

    scheduler_add(&check_switch, 50, 100);

    // Prints a new line
    scheduler_add(&send_newline, 100, 1000);

    // Critical: Read the ADC and checks if temp has changed
    // Sets temperaturechanged flag
    scheduler_add(&check_temperature, 200, 1000);

    // Prepare a char array of the temperature
    scheduler_add(&prepare_temperature, 600, 1000);

    // Sends the char array containing temperature
    scheduler_add(&send_temperature, 800, 1000);

    // Blinks according to the temperature
    scheduler_add(&blink_temperature, 1000, 0);
}

// Scheduler main function, dispatches tasks for execution
void scheduler_dispatch(void)
{
    // Updates tasks to be run this time
    scheduler_update();
    tByte i;
    // Goes through the array
    for (i = 0; i < TASK_MAX; i++)
    {
        // If task is due to run
        if (task[i].runflag > 0)
        {
            // Run the task aka C Magic
            (*task[i].taskptr)();
            // Reset the runflag
            task[i].runflag = 0;
            // If this is a one-time task, remove it
            if (task[i].period == 0)
            {
                scheduler_remove(i);
            }
        }
    }
}

// Adds task to the scheduler: task, delay, period. Period 0 means run once, then delete
// Alterntive 1 with typedef'ed pointer
//void scheduler_add(function_pointer taskfunction, tWord taskdelay, tWord taskperiod) {
// TODO Alternative 2 (N/A)
void scheduler_add(void (*taskfunction)(), tWord taskdelay, tWord taskperiod)
{

    tByte i = ZERO;
    // Find first empty slot
    while ((task[i].taskptr != 0) && (i < TASK_MAX))
    {
        i++;
    }

    // Task list is full
    if (i == TASK_MAX)
    {
        // TODO Error handling
        return;
    }

    // Add the task to the list
    task[i].taskptr = taskfunction;
    task[i].delay = taskdelay + 1;
    task[i].period = taskperiod;
    task[i].runflag = FALSE;
}

// Removes task from scheduler
void scheduler_remove(tByte i)
{
    // If slot is empty
    if (task[i].taskptr == ZERO)
    {
        // TODO Error handling
        return;
    }
    // Remove task from list
    task[i].taskptr = XERO;
    task[i].delay = ZERO;
    task[i].period = ZERO;
    task[i].runflag = FALSE;
}

// Selects the task due to run this tick
void scheduler_update(void)
{
    // An alternative to the flag would be to list the indices in a "to run"-array
    tByte i;
    // Update task array for dispatching
    for (i = 0; i < TASK_MAX; i++)
    {
        // Check if there is a task at this location
        if (task[i].taskptr)
        {
            // If the task is due to run now
            if (--task[i].delay == 0)
            {
                // Set the flag to run
                task[i].runflag = TRUE;
                // If it is to run again
                if (task[i].period)
                {
                    // Reset the delay
                    task[i].delay = task[i].period;
                }
            }
        }
    }

}
