CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -pedantic
DBGFLAGS=-ggdb
OBJ=Out

.PHONY: all
all: main.c heap.c heap.h 
	$(CC) $(CFLAGS) $(DBGFLAGS) -o $(OBJ) main.c heap.c


.PHONY: clean
clean:
	rm -rf $(OBJ) 
