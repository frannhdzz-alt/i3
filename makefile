# =================================================================
# File: Makefile
# Authors: Rodrigo and Mario
# Project: The Haunted Castle 
# =================================================================

# --- Directorios ---
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = lib
DOC_DIR = doc


CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -lscreen


_OBJ = game_loop.o game.o game_actions.o space.o command.o graphic_engine.o game_reader.o object.o player.o set.o character.o inventory.o link.o game_rules.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

EXEC = castle


TESTS = set_test character_test space_test inventory_test link_test object_test player_test

.PHONY: all clean run vrun test vtest doc directories


all: directories $(EXEC) $(TESTS)

directories:
	@mkdir -p $(OBJ_DIR) $(DOC_DIR) $(LIB_DIR)


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)



$(OBJ_DIR)/game_loop.o: $(SRC_DIR)/game_loop.c $(INC_DIR)/game.h $(INC_DIR)/game_actions.h $(INC_DIR)/graphic_engine.h $(INC_DIR)/game_reader.h $(INC_DIR)/command.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game.o: $(SRC_DIR)/game.c $(INC_DIR)/game.h $(INC_DIR)/space.h $(INC_DIR)/object.h $(INC_DIR)/player.h $(INC_DIR)/character.h $(INC_DIR)/link.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_actions.o: $(SRC_DIR)/game_actions.c $(INC_DIR)/game_actions.h $(INC_DIR)/game.h $(INC_DIR)/command.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/space.o: $(SRC_DIR)/space.c $(INC_DIR)/space.h $(INC_DIR)/types.h $(INC_DIR)/set.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/command.o: $(SRC_DIR)/command.c $(INC_DIR)/command.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/graphic_engine.o: $(SRC_DIR)/graphic_engine.c $(INC_DIR)/graphic_engine.h $(INC_DIR)/game.h $(INC_DIR)/command.h $(INC_DIR)/space.h $(INC_DIR)/player.h $(INC_DIR)/object.h $(INC_DIR)/character.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_reader.o: $(SRC_DIR)/game_reader.c $(INC_DIR)/game_reader.h $(INC_DIR)/game.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/object.o: $(SRC_DIR)/object.c $(INC_DIR)/object.h $(INC_DIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/player.o: $(SRC_DIR)/player.c $(INC_DIR)/player.h $(INC_DIR)/types.h $(INC_DIR)/inventory.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/set.o: $(SRC_DIR)/set.c $(INC_DIR)/set.h $(INC_DIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/character.o: $(SRC_DIR)/character.c $(INC_DIR)/character.h $(INC_DIR)/types.h $(INC_DIR)/inventory.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory.o: $(SRC_DIR)/inventory.c $(INC_DIR)/inventory.h $(INC_DIR)/types.h $(INC_DIR)/set.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/link.o: $(SRC_DIR)/link.c $(INC_DIR)/link.h $(INC_DIR)/types.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/game_rules.o: $(SRC_DIR)/game_rules.c $(INC_DIR)/game_rules.h $(INC_DIR)/game.h
	$(CC) $(CFLAGS) -c $< -o $@



$(OBJ_DIR)/set_test.o: $(SRC_DIR)/set_test.c $(INC_DIR)/set.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/character_test.o: $(SRC_DIR)/character_test.c $(INC_DIR)/character.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/space_test.o: $(SRC_DIR)/space_test.c $(INC_DIR)/space.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/inventory_test.o: $(SRC_DIR)/inventory_test.c $(INC_DIR)/inventory.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/link_test.o: $(SRC_DIR)/link_test.c $(INC_DIR)/link.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/object_test.o: $(SRC_DIR)/object_test.c $(INC_DIR)/object.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/player_test.o: $(SRC_DIR)/player_test.c $(INC_DIR)/player.h
	$(CC) $(CFLAGS) -c $< -o $@



set_test: $(OBJ_DIR)/set_test.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^

character_test: $(OBJ_DIR)/character_test.o $(OBJ_DIR)/character.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^

space_test: $(OBJ_DIR)/space_test.o $(OBJ_DIR)/space.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^

inventory_test: $(OBJ_DIR)/inventory_test.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^

link_test: $(OBJ_DIR)/link_test.o $(OBJ_DIR)/link.o
	$(CC) -o $@ $^

object_test: $(OBJ_DIR)/object_test.o $(OBJ_DIR)/object.o
	$(CC) -o $@ $^

player_test: $(OBJ_DIR)/player_test.o $(OBJ_DIR)/player.o $(OBJ_DIR)/inventory.o $(OBJ_DIR)/set.o
	$(CC) -o $@ $^



run: $(EXEC)
	./$(EXEC) castle.dat -l registro.txt

vrun: $(EXEC)
	valgrind --leak-check=full ./$(EXEC) castle.dat -l registro.txt

test: $(EXEC)
	./$(EXEC) castle.dat -l log_normal.txt < test_normal.cmd
	./$(EXEC) castle.dat -l log_errores.txt < test_errores.cmd
	./$(EXEC) castle_vacio.dat -l log_vacio.txt < test_vacio.cmd
	./$(EXEC) castle_error.dat -l log_dat_error.txt < test_normal.cmd

doc:
	doxygen Doxyfile

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) $(TESTS)
	rm -f *.txt
	rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex