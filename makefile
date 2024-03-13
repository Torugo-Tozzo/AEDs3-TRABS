CC = g++

# Flags for compilation (optional)
CFLAGS = -Wall  # Enable warnings (adjust as needed)

# Regras de compilação (Compilation rules)
all: main
	./main

main: main.o
	$(CC) $(CFLAGS) -o main main.o  # Link object file to create executable

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp  # Compile source code to object file

# Regra de limpeza (Cleaning rule)
clean:
	rm -f main main.o  # Remove executable and object file

