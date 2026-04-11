# =================================================================
# File: Makefile
# Authors: Rodrigo and Mario
# Project: The Haunted Castle 
# =================================================================

# Compiler configurations
# Use gcc as the compiler.
# Flags: -Wall (warnings), -ansi (standard C), -pedantic, -g (for debugging).
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

# Screen library:
# Tells the compiler to look for the library in the current folder (.)
LDFLAGS = -L. -lscreen

# List of all object files (.o) needed.
OBJ = game_loop.o game.o game_actions.o space.o command.o graphic_engine.o game_reader.o object.o player.o set.o character.o inventory.o link.o

# -----------------------------------------------------------------
# MAIN RULES
# -----------------------------------------------------------------

# Default rule: Compile the complete program
all: castle

# Linking: Joins all object files (.o) and the library to create the executable
castle: $(OBJ) 
	$(CC) -o castle $(OBJ) $(LDFLAGS)

# -----------------------------------------------------------------
# EXECUTION RULES
# -----------------------------------------------------------------

# Runs the game normally
run: castle
	./castle castle_i3.dat -l registro.txt

# Runs the game with valgrind
vrun: castle
	valgrind --leak-check=full ./castle castle_i3.dat -l registro.txt

# Test rule: Quick check (runs the game and then cleans up)
test: run
	make clean

# Test rule: Quick check (runs the game with valgrind and then cleans up)
vtest: vrun
	make clean

# Deletes temporary object files and the executable
clean:
	rm -f *.o $(EXEC) castle
	rm -f *.txt 
# -----------------------------------------------------------------
# MODULE COMPILATION (.c -> .o)
# -----------------------------------------------------------------

game_loop.o: game_loop.c game.h game_actions.h graphic_engine.h command.h game_reader.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h space.h types.h player.h object.h character.h
	$(CC) $(CFLAGS) -c game.c

game_actions.o: game_actions.c game_actions.h game.h
	$(CC) $(CFLAGS) -c game_actions.c

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c

command.o: command.c command.h types.h
	$(CC) $(CFLAGS) -c command.c

graphic_engine.o: graphic_engine.c graphic_engine.h game.h libscreen.h
	$(CC) $(CFLAGS) -c graphic_engine.c

game_reader.o: game_reader.c game_reader.h game.h space.h
	$(CC) $(CFLAGS) -c game_reader.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

character.o: character.c character.h types.h
	$(CC) $(CFLAGS) -c character.c

inventory.o: inventory.c inventory.h set.h types.h
	$(CC) $(CFLAGS) -c inventory.c

link.o: link.c link.h types.h
	$(CC) $(CFLAGS) -c link.c

# -----------------------------------------------------------------
# TEST RULES
# -----------------------------------------------------------------
set_test: set_test.o set.o
	$(CC) -o set_test set_test.o set.o

character_test: character_test.o character.o
	$(CC) -o character_test character_test.o character.o

space_test: space_test.o space.o set.o
	$(CC) -o space_test space_test.o space.o set.o

set_test.o: set_test.c set.h types.h
	$(CC) $(CFLAGS) -c set_test.c

character_test.o: character_test.c character.h types.h
	$(CC) $(CFLAGS) -c character_test.c

space_test.o: space_test.c space.h types.h set.h
	$(CC) $(CFLAGS) -c space_test.c


