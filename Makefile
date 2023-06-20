CC = gcc
CFLAGS = -Wall -Wextra -g -Og $(shell pkg-config --cflags sdl2 sdl2_image)
LDFLAGS = $(shell pkg-config --libs sdl2 sdl2_image) -lm

all: main

main: main.o
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm *.o main
