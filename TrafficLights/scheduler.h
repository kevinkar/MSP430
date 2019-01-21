#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "tlight.h"

// Typedef our custom struct "stask" for the tasks.
typedef struct stask
{
    // Pointer for the function (name).
    void (*taskptr)();
    // Delay in ticks until first execution.
    tWord delay;
    // Period in ticks between executions. 0 means run once.
    tWord period;
} stask;

// Maximum amount of task handled. Adjust if necessary.
#define TASK_MAX 3

// The task list as an array
static stask task[TASK_MAX];

// Initialize scheduler for use. Add the tasks to run.
void scheduler_init(void);

// Ticks all tasks and execute next in line.
void scheduler_dispatch(void);

// Add a task to the scheduler's list. Values in ms.
void scheduler_add(void (*function)(), tWord ms_delay, tWord ms_period);

// Remove a task from the scheduler's list. Only used internally.
void scheduler_remove(tByte i);

#endif
