# RTOS Scheduler Simulator

A priority-based preemptive scheduler written in C, simulating the core concepts of FreeRTOS and QNX on a standard Linux machine — no hardware required.

## What is this project?

This project simulates how a Real-Time Operating System (RTOS) scheduler works inside embedded systems like automotive ECUs. It implements:

- Task Control Block (TCB) design
- Priority-based preemptive scheduling
- Task states: READY → RUNNING → BLOCKED → READY
- Tick-based delay (equivalent to vTaskDelay in FreeRTOS)

## Why is this relevant?

Modern vehicles like those built on Toyota's Arene platform contain 100+ ECUs, each running an RTOS scheduler. This project demonstrates the core concepts used in automotive embedded software development.

## Project Structure

| File | Purpose |
|---|---|
| scheduler.h | Task Control Block and function declarations |
| scheduler.c | Scheduler logic — tick, priority, blocking |
| main.c | Three simulated vehicle tasks |
| test_scheduler.c | Unit tests |
| Makefile | Build system |

## How to Build and Run

    # Build
    make

    # Run simulator
    ./rtos_sim

    # Run unit tests
    make test

    # Clean build files
    make clean

## Sample Output

    --- Tick 1 ---
    [RUN ] task='SpeedMonitor' priority=0
      SpeedMonitor: vehicle speed = 62 km/h
    [BLK ] task='SpeedMonitor' sleeping for 2 ticks

    --- Tick 2 ---
    [RUN ] task='Dashboard' priority=1
      Dashboard: updating display

    --- Tick 3 ---
    [RUN ] task='SpeedMonitor' priority=0
      SpeedMonitor: vehicle speed = 64 km/h

## Concepts Mapped to Real RTOS

| This Project | FreeRTOS | QNX |
|---|---|---|
| TCB struct | TCB_t | pthread |
| task_delay(n) | vTaskDelay(n) | delay() |
| TASK_BLOCKED | eBlocked | CONDVAR |
| pick_next_task() | Scheduler core | Pulse system |

## Tech Stack

- Language: C (C11 standard)
- Build: GCC + Makefile
- Testing: Custom unit tests with assert
- Platform: Linux (Ubuntu)

## Author

Sujnan — Aspiring Embedded Software Engineer