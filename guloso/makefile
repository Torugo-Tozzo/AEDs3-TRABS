CC = g++
CFLAGS = -Wall

all: guloso

guloso: guloso.o
	$(CC) $(CFLAGS) -o guloso guloso.o
	./guloso

guloso.o: guloso.cpp
	$(CC) $(CFLAGS) -c guloso.cpp

clean:
	rm -f guloso guloso.o
