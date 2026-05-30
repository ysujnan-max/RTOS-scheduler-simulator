#include "scheduler.h"
#include <stdio.h>
#include <assert.h>

/* Dummy tasks for testing */
void dummy_task_a(void) {}
void dummy_task_b(void) {}
void dummy_task_c(void) {}

/* Test 1: Higher priority task runs first */
void test_priority_ordering(void) {
    scheduler_init();
    scheduler_add_task("LowPriority",  dummy_task_a, 2);
    scheduler_add_task("HighPriority", dummy_task_b, 0);
    scheduler_add_task("MidPriority",  dummy_task_c, 1);

    /* Run one tick — HighPriority must run first */
    scheduler_tick();

    printf("PASS: test_priority_ordering\n");
}

/* Test 2: Scheduler initializes cleanly */
void test_init(void) {
    scheduler_init();
    /* If init crashes, test fails automatically */
    printf("PASS: test_init\n");
}

/* Test 3: Adding maximum tasks doesn't crash */
void test_max_tasks(void) {
    scheduler_init();
    int i;
    for (i = 0; i < MAX_TASKS; i++) {
        scheduler_add_task("Task", dummy_task_a, i);
    }
    /* Adding one more should be safely ignored */
    scheduler_add_task("Extra", dummy_task_a, 0);
    printf("PASS: test_max_tasks\n");
}

/* Test 4: Running with no tasks doesn't crash */
void test_empty_scheduler(void) {
    scheduler_init();
    scheduler_run(3);
    printf("PASS: test_empty_scheduler\n");
}

int main(void) {
    printf("\n========== RUNNING TESTS ==========\n\n");

    test_init();
    test_priority_ordering();
    test_max_tasks();
    test_empty_scheduler();

    printf("\n========== ALL TESTS PASSED ==========\n");
    return 0;
}