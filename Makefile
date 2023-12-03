CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all clean

all: ./program

TARGET = main

./program: $(TARGET).o AVL/arvore_avl.o RedBlack/RedBlack.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c AVL/arvore_avl.h RedBlack/RedBlack.h
	$(CC) $(CFLAGS) -c $<

arvore_avl.o: AVL/arvore_avl.c AVL/arvore_avl.h
	$(CC) $(CFLAGS) -c $<

RedBlack.o: RedBlack/RedBlack.c RedBlack/RedBlack.h
	$(CC) $(CFLAGS) -c $<