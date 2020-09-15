CC=gcc
CFLAGS=-I. -O2 -Wall
DEPS = barrier.h common_threads.h rand.h util.h
OBJ = main.o barrier.o rand.o util.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	chmod +x main

all: main

clean:
	rm -rf main *.o main.o.dSYM