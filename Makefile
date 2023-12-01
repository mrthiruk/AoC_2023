CC := gcc
CFLAGS := -Wall -std=c99

1: day_01.c
	$(CC) $(CFLAGS) -o 1.out day_01.c
