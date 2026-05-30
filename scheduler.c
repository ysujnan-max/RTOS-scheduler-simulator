#include "scheduler.h"
#include <stdio.h>
#include <string.h>

static TCB      task_list[MAX_TASKS];
static int      task_count   = 0;
static int      current_task = -1;
static uint32_t sys_tick     = 0;

void scheduler_init(void) {
    memset(task_list, 0, sizeof(task_list));
    task_count   = 0;
    current_task = -1;
    sys_tick     = 0;
}

void scheduler_add_task(const char *name, TaskFunc func, uint8_t priority) {
    if (task_count >= MAX_TASKS) return;
    task_list[task_count].name        = name;
    task_list[task_count].func        = func;
    task_list[task_count].state       = TASK_READY;
    task_list[task_count].priority    = priority;
    task_list[task_count].delay_ticks = 0;
    task_count++;
}

static void update_blocked_tasks(void) {
    int i;
    for (i = 0; i < task_count; i++) {
        if (task_list[i].state == TASK_BLOCKED) {
            if (task_list[i].delay_ticks > 0) {
                task_list[i].delay_ticks--;
            }
            if (task_list[i].delay_ticks == 0) {
                task_list[i].state = TASK_READY;
            }
        }
    }
}

static int pick_next_task(void) {
    int best = -1;
    int i;
    for (i = 0; i < task_count; i++) {
        if (task_list[i].state != TASK_READY) continue;
        if (best == -1 || task_list[i].priority < task_list[best].priority) {
            best = i;
        }
    }
    return best;
}

void scheduler_tick(void) {
    int next;
    sys_tick++;
    printf("\n--- Tick %u ---\n", sys_tick);

    update_blocked_tasks();

    next = pick_next_task();
    if (next == -1) {
        printf("[IDLE] no ready tasks\n");
        return;
    }

    if (current_task != -1 && current_task != next) {
        if (task_list[current_task].state == TASK_RUNNING) {
            task_list[current_task].state = TASK_READY;
        }
    }

    current_task = next;
    task_list[current_task].state = TASK_RUNNING;

    printf("[RUN ] task='%s' priority=%d\n",
           task_list[current_task].name,
           task_list[current_task].priority);

    task_list[current_task].func();

    if (task_list[current_task].state == TASK_RUNNING) {
        task_list[current_task].state = TASK_READY;
    }
}

void task_delay(uint32_t ticks) {
    if (current_task == -1) return;
    task_list[current_task].state       = TASK_BLOCKED;
    task_list[current_task].delay_ticks = ticks;
    printf("[BLK ] task='%s' sleeping for %u ticks\n",
           task_list[current_task].name, ticks);
}

void scheduler_run(uint32_t ticks) {
    uint32_t t;
    for (t = 0; t < ticks; t++) {
        scheduler_tick();
    }
}