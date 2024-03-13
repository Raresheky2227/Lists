CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2 -pg

all: sort improved_sort quicksort

sort: sort.c
	$(CC) $(CFLAGS) -o sort sort.c

improved_sort: improved_sort.c
	$(CC) $(CFLAGS) -o improved_sort improved_sort.c

quicksort: quicksort.c
	$(CC) $(CFLAGS) -o quicksort quicksort.c

clean:
	rm -f sort improved_sort quicksort gmon.out
