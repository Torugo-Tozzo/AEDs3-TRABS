CC = g++
CFLAGS = -Wall

all: forcaBruta

forcaBruta: forcaBruta.o
	$(CC) $(CFLAGS) -o forcaBruta forcaBruta.o
	./forcaBruta

forcaBruta.o: forcaBruta.cpp
	$(CC) $(CFLAGS) -c forcaBruta.cpp

clean:
	rm -f forcaBruta forcaBruta.o
