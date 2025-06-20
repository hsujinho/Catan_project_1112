CC = gcc
CFLAGS = -Wall -Wextra -g -Og $(shell pkg-config --cflags sdl2 sdl2_image)
LDFLAGS = $(shell pkg-config --libs sdl2 sdl2_image) -lm

all: main

OBJS = main.o render.o game_init.o utils.o

main: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm *.o main
