# =================================================================
# File: Makefile
# Authors: Rodrigo and Mario
# Project: The Haunted Castle 
# =================================================================

# --- Directorios (Requisito C4) ---
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
DOC_DIR = doc

# --- Compilador y Flags (Requisito C2) ---
CC = gcc
# Añadimos -I$(INC_DIR) para que gcc sepa buscar los .h en la carpeta include/
CFLAGS = -Wall -ansi -pedantic -g -I$(INC_DIR)

# --- Librerías ---
# Cambiamos -L. a -L$(LIB_DIR) para que busque libscreen.a en lib/
LDFLAGS = -L$(LIB_DIR) -lscreen

# --- Archivos Objeto ---
_OBJ = game_loop.o game.o game_actions.o space.o command.o graphic_engine.o game_reader.o object.o player.o set.o character.o inventory.o link.o game_rules.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

EXEC = castle

.PHONY: all clean run vrun test vtest doc directories

all: directories $(EXEC)


directories:
	@mkdir -p $(OBJ_DIR) $(DOC_DIR) $(LIB_DIR)


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@



run: $(EXEC)
	./$(EXEC) castle.dat -l registro.txt

vrun: $(EXEC)
	valgrind --leak-check=full ./$(EXEC) castle.dat -l registro.txt

test: $(EXEC)
	./$(EXEC) castle.dat -l log_normal.txt < test_normal.cmd
	./$(EXEC) castle.dat -l log_errores.txt < test_errores.cmd


doc:
	doxygen Doxyfile

set_test: directories $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o

character_test: directories $(OBJ_DIR)/character_test.o $(OBJ_DIR)/character.o
	$(CC) -o $@ $(OBJ_DIR)/character_test.o $(OBJ_DIR)/character.o

space_test: directories $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o


clean:
	rm -f obj/*.o castle set_test character_test space_test
	rm -f *.txt
	rm -rf doc/html doc/latex