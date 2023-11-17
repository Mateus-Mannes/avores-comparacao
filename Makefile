CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all clean

all: ./program

TARGET = main

./program: $(TARGET).o AVL/arvore_avl.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c AVL/arvore_avl.h
	$(CC) $(CFLAGS) -c $^

arvore.o: AVL/arvore_avl.c AVL/arvore_avl.h
	$(CC) $(CFLAGS) -c $^