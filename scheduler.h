#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define MAX_TASKS 8

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED
} TaskState;

typedef void (*TaskFunc)(void);

typedef struct {
    const char  *name;
    TaskFunc     func;
    TaskState    state;
    uint8_t      priority;
    uint32_t     delay_ticks;
} TCB;

void scheduler_init(void);
void scheduler_add_task(const char *name, TaskFunc func, uint8_t priority);
void scheduler_tick(void);
void scheduler_run(uint32_t ticks);
void task_delay(uint32_t ticks);

#endif