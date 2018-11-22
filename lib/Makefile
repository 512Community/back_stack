CC = gcc

CFLAGS= -g -fPIC
OBJ= put_crash.o

target=libput_crash.so

lib:$(OBJ)
	$(CC) $(CFLAGS) -shared $^ -o $(target)
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@

clean:
	rm -rf *.o $(target)
