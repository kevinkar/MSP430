/*
 * TODO Smarter arrays:
 * The array could be handled much better, allowing for shrinking and growing of the task list.
 *
 * NOTE: This is a "forgetting" scheduler. A task can not be queued to run multiple times if there happens to be some issues with the timing.
 * The alternative would be to count with a run flag how many times we are supposed to still execute the task in question
 *
 * NOTE: The add function deals in milliseconds, but the internals are based only on timer ticks.
 *
 */

#include "scheduler.h"

// Initialize scheduler for use. Add the tasks to run.
void scheduler_init(void)
{

}

// Ticks all tasks and execute next in line.
void scheduler_dispatch(void)
{
    tWord i;
    for (i = 0; i < TASK_MAX; i++)
    {            // Iterates the task list.
        if (task[i].taskptr)
        {                  // Task at this location.
            if (--task[i].delay == 0)
            {         // Tick the delay, task is due to execute.
                (*task[i].taskptr)();           // Executes task.
                task[i].delay = task[i].period; // Resets tick delay.
                if (task[i].period == 0)
                {      // Once only task.
                    scheduler_remove(i);        // ... is removed.
                }
            }
        }
    }
}

// Add a task to the scheduler's list. Values in ms.
void scheduler_add(void (*function)(), tWord ms_delay, tWord ms_period)
{

    tWord i = 0;
    // Find first empty slot.
    while ((task[i].taskptr != 0) && (i < TASK_MAX))
    {
        i++;
    }
    // Task list is full.
    if (i == TASK_MAX)
    {
        // Error handling code.
        uart_write("ERROR: Scheduler overflow");   // Not very advanced :D
        return;
    }

    // Timing is not exact
    //if ((ms_delay%TIMER_TICKS) || (ms_period%TIMER_TICKS)) {
    // TODO Error-handling. Non-critical timing error. Warn or ignore?
    //uart_write("WARNING: Inaccurate timing.");
    //return;
    //}

    // Add the task to the list.
    task[i].taskptr = function;
    task[i].delay = (ms_delay / TIMER_TICKS) + 1; // Ticks account for timer stepping
    task[i].period = (ms_period / TIMER_TICKS); // Ticks account for timer stepping

}

// Remove a task from the scheduler's list. Only used internally.
void scheduler_remove(tByte i)
{

    // Reset all the fields.
    task[i].taskptr = XERO;
    task[i].delay = ZERO;
    task[i].period = ZERO;

}
