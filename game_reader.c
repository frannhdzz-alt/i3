/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#include "game_reader.h"
#include "space.h" 
#include "object.h"
#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_load_spaces(Game *game, char *filename);
Status game_load_objects(Game *game, char *filename);
Status game_load_characters(Game *game, char *filename);

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(*game, filename) == ERROR) {
    return ERROR;
  }

  if (game_load_objects(*game, filename) == ERROR) {
    return ERROR;
  }

  if (game_load_characters(*game, filename) == ERROR) {
    return ERROR;
  }

  game_set_player_location(*game, game_get_space_id_at(*game, 0));

  return OK;
}

Status game_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);

        /* Read the graphic description if present */
        toks = strtok(NULL, "|\n");
        if (toks) {
          space_set_gdesc(space, 0, toks);
          space_set_gdesc(space, 1, strtok(NULL, "|\n"));
          space_set_gdesc(space, 2, strtok(NULL, "|\n"));
          space_set_gdesc(space, 3, strtok(NULL, "|\n"));
          space_set_gdesc(space, 4, strtok(NULL, "|\n"));
        }
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}

Status game_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Object *object = NULL;
  Status status = OK;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);
      toks = strtok(NULL, "|\n");

      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        if (toks) object_set_description(object, toks);
        game_add_object(game, object);
        game_set_object_location(game, location, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}

Status game_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[7] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  int health = 0, friendly = 0;
  Character *character = NULL;
  Status status = OK;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      strcpy(message, toks);
      toks = strtok(NULL, "|");
      location = atol(toks);

      character = character_create(id);
      if (character != NULL) {
        character_set_name(character, name);
        character_set_gdesc(character, gdesc);
        character_set_health(character, health);
        character_set_friendly(character, friendly == 1 ? TRUE : FALSE);
        character_set_message(character, message);
        
        game_add_character(game, character);
        game_set_character_location(game, location, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}