#include "scheduler.h"
#include <stdio.h>

/* Task 1 - Speed Monitor (highest priority) */
void task_speed_monitor(void) {
    static int speed = 60;
    speed += 2;
    printf("  SpeedMonitor: vehicle speed = %d km/h\n", speed);
    task_delay(2);
}

/* Task 2 - Dashboard (medium priority) */
void task_dashboard(void) {
    printf("  Dashboard: updating display\n");
    task_delay(3);
}

/* Task 3 - Logger (lowest priority) */
void task_logger(void) {
    printf("  Logger: writing to log\n");
    task_delay(5);
}

int main(void) {
    scheduler_init();

    scheduler_add_task("SpeedMonitor", task_speed_monitor, 0);
    scheduler_add_task("Dashboard",    task_dashboard,     1);
    scheduler_add_task("Logger",       task_logger,        2);

    scheduler_run(20);

    return 0;
}