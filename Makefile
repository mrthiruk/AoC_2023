CC := gcc
CFLAGS := -g -Wall -std=c99 -I.

1: day_01.c
	$(CC) $(CFLAGS) -o 1.out day_01.c

2: day_02.c
	$(CC) $(CFLAGS) -o 2.out day_02.c

3: day_03.c
	$(CC) $(CFLAGS) -o 3.out day_03.c
