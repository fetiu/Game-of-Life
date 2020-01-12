CC = gcc
CFLAGS = -Ilife/src -Ilife/test/support #-DVERBOSE
TARGET = life

$(TARGET): objects
	$(CC) -o gol *.o

objects:
	$(CC) $(CFLAGS) -c main.c life/src/*.c life/test/support/*.c

clean:
	rm *.o gol

