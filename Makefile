# Makefile
CC = gcc
CFLAGS = -Wall -std=c99

all: sum-nbo

sum-nbo: sum_nbo.o
	$(CC) $(CFLAGS) -o sum-nbo sum_nbo.o

sum_nbo.o: sum_nbo.c sum_nbo.h
	$(CC) $(CFLAGS) -c sum_nbo.c

clean:
	rm -f sum-nbo
	rm -f *.o
