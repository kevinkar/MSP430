#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "main.h"

/*
 * SCHEDULER definitions
 */

// Alterntive 1 with typedef'ed pointer
//typedef void (*function_pointer) ();
// TODO Alternative 2 cancel this typedef
//Total 7 bytes for each task
typedef struct sch_task
{
    //Pointer to the task(must be 'void (void)')
    // Alternative 1 bypassed
    //function_pointer taskptr;
    void (*taskptr)();
    // TODO Alternative 2 (N/A)
    //void (*taskptr)(void);
    //Delay(ticks) until the function will be run for the first time. 0 means run once
    tWord delay;
    //Interval(ticks) between subsequent runs
    tWord period;
    //Incremented(by scheduler) when task is due to execute
    tByte runflag;
} sch_task;

#define TASK_MAX 7

static sch_task task[TASK_MAX];

void scheduler_init(void);

void scheduler_dispatch(void);

// Alterntive 1 with typedef'ed pointer
// Call by appending function's name iwth an ampersand like '&function'
//void scheduler_add(function_pointer taskfunction, tWord taskdelay, tWord taskperiod);
// TODO Alternative 2 (N/A)
void scheduler_add(void (*taskfunction)(), tWord taskdelay, tWord taskperiod);

void scheduler_remove(tByte i);

void scheduler_update(void);

#endif
