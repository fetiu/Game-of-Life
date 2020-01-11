CC = gcc
CFLAGS = -Isrc -Itest/support
TARGET = life

$(TARGET): objects
	$(CC) $(CFLAGS) -o life *.o

objects:
	$(CC) $(CFLAGS) -c main.c src/*.c test/support/*.c

clean:
	rm *.o life

