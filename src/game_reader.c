/**
 * @brief It implements the game reader module
 *
 * @file game_reader.c
 * @author Rodrigo, Mario and Francisco
 * @version 2.0
 * @date 13-04-2026
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
Status game_load_players(Game *game, char *filename);
Status game_load_links(Game *game, char *filename);

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(*game, filename) == ERROR) return ERROR;
  if (game_load_links(*game, filename) == ERROR) return ERROR;
  if (game_load_objects(*game, filename) == ERROR) return ERROR;
  if (game_load_players(*game, filename) == ERROR) return ERROR;
  if (game_load_characters(*game, filename) == ERROR) return ERROR;


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
  
  int health = 0, movable = 0;
  Id dependency = NO_ID, open = NO_ID;

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

      toks = strtok(NULL, "|");

      object = object_create(id);
      if (object != NULL) {
        object_set_name(object, name);
        if (toks) object_set_description(object, toks);

        toks = strtok(NULL, "|");
        if (toks) health = atoi(toks);
        object_set_health(object, health);

        toks = strtok(NULL, "|");
        if (toks) movable = atoi(toks);
        object_set_movable(object, movable == 1 ? TRUE : FALSE);

        toks = strtok(NULL, "|");
        if (toks) dependency = atol(toks);
        object_set_dependency(object, dependency);
        toks = strtok(NULL, "|\r\n");
        if (toks) open = atol(toks);
        object_set_open(object, open);
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
  
      toks = strtok(NULL, "|\r\n");
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

Status game_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[7] = "";
  char *toks = NULL;
  Id id = NO_ID, location = NO_ID;
  int health = 0;
  Player *player = NULL;
  Status status = OK;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (!file) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      
      toks = strtok(NULL, "|");
      strcpy(gdesc, toks);
      
      toks = strtok(NULL, "|");
      location = atol(toks);
      
      toks = strtok(NULL, "|");
      health = atoi(toks);
      
      toks = strtok(NULL, "|");

      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_gdesc(player, gdesc);
        player_set_location(player, location);
        player_set_health(player, health);
        game_add_player(game, player);
        game_set_space_discovered(game, location, TRUE);
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}

Status game_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, origin = NO_ID, dest = NO_ID;
  Direction dir = N;
  int open = 0;
  Link *link = NULL;
  Status status = OK;

  if (!filename) return ERROR;

  file = fopen(filename, "r");
  if (!file) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      
      toks = strtok(NULL, "|");
      origin = atol(toks);
      
      toks = strtok(NULL, "|");
      dest = atol(toks);
      
      toks = strtok(NULL, "|");
      dir = (Direction)atoi(toks);
      
      toks = strtok(NULL, "|");
      open = atoi(toks);

      link = link_create(id);
      if (link != NULL) {
        link_set_name(link, name);
        link_set_origin(link, origin);
        link_set_destination(link, dest);
        link_set_direction(link, dir);
        link_set_open(link, open == 1 ? TRUE : FALSE);
        
        game_add_link(game, link); 
      }
    }
  }

  if (ferror(file)) status = ERROR;
  fclose(file);
  return status;
}

