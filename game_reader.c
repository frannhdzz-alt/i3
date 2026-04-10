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
#include "game.h"
#include "space.h"
#include "object.h"
#include "character.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status game_load_spaces(Game *game, char *filename);
Status game_load_objects(Game *game, char *filename);
Status game_load_characters(Game *game, char *filename);
Status game_load_player(Game *game, char *filename);

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


  if (game_load_player(*game, filename) == ERROR) {
    return ERROR;
  }

  return OK;
}

Status game_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  Status status = OK;
  int i;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (!file) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      space = space_create(id);
      if (space != NULL) {
        space_set_name(space, name);


        for (i = 0; i < 5; i++) {
          toks = strtok(NULL, "|");
          if (toks) {
            space_set_gdesc(space, i, toks);
          }
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

Status game_load_player(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char obj_list[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  Player *player = NULL;
  Status status = OK;
  Id obj_id = NO_ID;
  char *token = NULL;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {

      toks = strtok(line + 3, "|");
      if (!toks) continue;
      id = atol(toks);

      toks = strtok(NULL, "|");
      if (toks) strcpy(name, toks);

      toks = strtok(NULL, "|");
      if (toks) location = atol(toks);

      toks = strtok(NULL, "|\n");
      if (toks) strcpy(obj_list, toks);

      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        
      
        player_set_gdesc(player, "^O^");

        /* Procesar objetos separados por comas */
        token = strtok(obj_list, ",");
        while (token) {
          obj_id = atol(token);
          if (obj_id != NO_ID) {
            player_add_object(player, obj_id);
          }
          token = strtok(NULL, ",");
        }

        
        game_set_player(game, player);
        game_set_player_location(game, location);
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}