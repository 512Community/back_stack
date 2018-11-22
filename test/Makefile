CC = gcc

LIB = ../lib/libput_crash.so
INCLUDE= -I../include
target=test
all:
	$(CC) -g test.c -o $(target) $(LIB) $(INCLUDE)
clean:
	rm -rf *.o $(target)
