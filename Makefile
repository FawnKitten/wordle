
CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -ansi -O0 -g

main: main.c
	$(CC) $(CFLAGS) -o main main.c
