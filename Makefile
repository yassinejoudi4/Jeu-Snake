CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LIBS = $(shell sdl2-config --libs) -lm

SRCS = main.c carte.c serpent.c
OBJS = $(SRCS:.c=.o)
EXEC = snake

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(SDL_LIBS)

main.o: main.c carte.h serpent.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c main.c

carte.o: carte.c carte.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c carte.c

serpent.o: serpent.c serpent.h carte.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c serpent.c

clean:
	rm -f $(OBJS) $(EXEC)

install: $(EXEC)
	cp $(EXEC) /usr/local/bin/

.PHONY: all clean install
