CC = gcc
CFLAGS = -Ilife/src -Ilife/test/support #-DVERBOSE
TARGET = life

$(TARGET): objects
	$(CC) -o conway *.o

objects:
	$(CC) $(CFLAGS) -c GoL.c life/src/*.c life/test/support/*.c

clean:
	rm *.o conway

