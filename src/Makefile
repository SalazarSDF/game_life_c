CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_XOPEN_SOURCE=500

all: main

main: game_of_life.o graphics.o game_logic.o
	$(CC) $(CFLAGS) game_of_life.o graphics.o game_logic.o -o main

game_of_life.o: game_of_life.c game_logic.h graphics.h
	$(CC) $(CFLAGS) -c game_of_life.c

game_logic.o: game_logic.c game_logic.h
	$(CC) $(CFLAGS) -c game_logic.c

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c graphics.c

clear:
	rm -f *.o