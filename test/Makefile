CC = gcc

LIB = -L../lib -lput_crash
INCLUDE= -I../include
CFLAGS= -g3 -Wl,-rpath=$(shell pwd)/../lib
target=BackStackDemo

all:
	$(CC) $(CFLAGS) test.c -o $(target) $(LIB) $(INCLUDE) 
	mv $(target) ../
clean:
	rm -rf *.o ../$(target)
