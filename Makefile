CC = gcc
CFLAGS = -Wall
LIB = -lncursesw
DIRS = src/*.c src/maze/*.c src/pathfinding/*.c
EXE = MAPDA

all:
	$(CC) $(CFLAGS) $(DIRS) -o $(EXE) $(LIB)
	./$(EXE) -r 10 10