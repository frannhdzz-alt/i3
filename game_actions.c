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

  if (!obj_name || obj_name[0] == '\0' || player_get_object(player) != NO_ID) return;

  for (i = 1; i < MAX_OBJECTS; i++) {
    Object *o = game_get_object(game, i);
    if (o && strcasecmp(object_get_name(o), obj_name) == 0) {
      obj_id = i;
      break;
    }
  }

  if (obj_id != NO_ID && space_has_object(current_space, obj_id) == TRUE) {
    player_set_object(player, obj_id);
    space_del_object(current_space, obj_id);
  }
}

void game_actions_drop(Game *game) {
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Id obj_id = NO_ID;

  if (!game) return;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  obj_id = player_get_object(player);

  if (obj_id == NO_ID) return;

  space_add_object(current_space, obj_id);
  player_set_object(player, NO_ID);
}

void game_actions_move(Game *game) {
  Id current_id = NO_ID;
  Id dest_id = NO_ID;
  const char *arg = NULL;
  Direction dir = N;

  if (!game) return;

  arg = command_get_arg(game_get_last_command(game));
  if (!arg) return;

if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0) {
    dir = N;
  } else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0) {
    dir = S;
  } else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0) {
    dir = E;
  } else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0) {
    dir = W;
  } else {
    return;
  }

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;

  if (game_connection_is_open(game, current_id, dir) == TRUE) {
    dest_id = game_get_connection(game, current_id, dir);
    if (dest_id != NO_ID) {
      game_set_player_location(game, dest_id);
    }
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
    case MOVE: game_actions_move(game); break;
    case TAKE: game_actions_take(game); break;
    case DROP: game_actions_drop(game); break;
    case ATTACK: game_actions_attack(game); break;
    case CHAT: game_actions_chat(game); break;
    default: break;
  }
  return OK;
}