CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: rtos_sim

rtos_sim: main.c scheduler.c scheduler.h
	$(CC) $(CFLAGS) -o rtos_sim main.c scheduler.c

test: test_scheduler.c scheduler.c scheduler.h
	$(CC) $(CFLAGS) -o test_runner test_scheduler.c scheduler.c
	./test_runner

clean:
	rm -f rtos_sim test_runner