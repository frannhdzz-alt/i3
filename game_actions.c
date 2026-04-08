/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* Private functions */
void game_actions_unknown(Game *game) {}
void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id dest_id = NO_ID;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;
  
  dest_id = space_get_south(game_get_space(game, current_id));
  if (dest_id != NO_ID) game_set_player_location(game, dest_id);
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id dest_id = NO_ID;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;
  
  dest_id = space_get_north(game_get_space(game, current_id));
  if (dest_id != NO_ID) game_set_player_location(game, dest_id);
}

void game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id dest_id = NO_ID;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;
  
  dest_id = space_get_west(game_get_space(game, current_id));
  if (dest_id != NO_ID) game_set_player_location(game, dest_id);
}

void game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id dest_id = NO_ID;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;
  
  dest_id = space_get_east(game_get_space(game, current_id));
  if (dest_id != NO_ID) game_set_player_location(game, dest_id);
}

void game_actions_take(Game *game) {
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Command *cmd = NULL;
  const char *obj_name = NULL;
  Id obj_id = NO_ID;
  int i;

  if (!game) return;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  cmd = game_get_last_command(game);
  obj_name = command_get_arg(cmd);


  if (!obj_name || obj_name[0] == '\0') return;


  for (i = 1; i < MAX_OBJECTS; i++) {
    Object *o = game_get_object(game, i);
    if (o && strcmp(object_get_name(o), obj_name) == 0) {
      obj_id = i;
      break;
    }
  }


  if (obj_id == NO_ID || space_has_object(current_space, obj_id) == FALSE) return;

  
  if (player_has_object(player, obj_id) == TRUE) return;

  
  if (player_add_object(player, obj_id) == OK) {
    space_del_object(current_space, obj_id);
  }
}

void game_actions_drop(Game *game) {
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Command *cmd = NULL;
  const char *obj_name = NULL;
  Id obj_id = NO_ID;
  Object *obj = NULL;
    int i;

  if (!game) return;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  cmd = game_get_last_command(game);
  obj_name = command_get_arg(cmd);

  /* No hay nombre de objeto */
  if (!obj_name || obj_name[0] == '\0') return;

  /* Buscar el objeto por nombre entre los objetos del juego */

  for (i = 1; i < MAX_OBJECTS; i++) {
    obj = game_get_object(game, i);
    if (obj && strcmp(object_get_name(obj), obj_name) == 0) {
      obj_id = i;
      break;
    }
  }

  /* Si no existe ese objeto, no se puede soltar */
  if (obj_id == NO_ID) return;

  /* Si el jugador no tiene ese objeto, no puede soltarlo */
  if (player_has_object(player, obj_id) == FALSE) return;

  /* Soltar el objeto */
  if (player_del_object(player, obj_id) == OK) {
    space_add_object(current_space, obj_id);
  }
}

void game_actions_attack(Game *game) {
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Id char_id = NO_ID;
  Character *c = NULL;
  int roll = 0;

  if (!game) return;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  char_id = space_get_character(current_space);

  if (char_id != NO_ID) {
    c = game_get_character(game, char_id);
    if (c && character_get_friendly(c) == FALSE) {
      roll = rand() % 10;
      if (roll <= 4) {
        player_set_health(player, player_get_health(player) - 1);
        if (player_get_health(player) <= 0) {
          game_set_finished(game, TRUE); /* Game Over */
        }
      } else {
        character_set_health(c, character_get_health(c) - 1);
        if (character_get_health(c) <= 0) {
          space_set_character(current_space, NO_ID); /* Enemy dies */
        }
      }
    }
  }
}

void game_actions_inspect(Game *game) {
}

void game_actions_chat(Game *game) {
}

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;
  
  if (!game || !command) return ERROR;
  
  game_set_last_command(game, command);
  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN: game_actions_unknown(game); break;
    case EXIT: game_actions_exit(game); break;
    case NEXT: game_actions_next(game); break;
    case BACK: game_actions_back(game); break;
    case LEFT: game_actions_left(game); break;
    case RIGHT: game_actions_right(game); break;
    case TAKE: game_actions_take(game); break;
    case DROP: game_actions_drop(game); break;
    case ATTACK: game_actions_attack(game); break;
    case INSPECT: game_actions_inspect(game); break;
    case CHAT: game_actions_chat(game); break;
    default: break;
  }
  return OK;
}