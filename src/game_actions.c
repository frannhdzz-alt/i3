/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Rodrigo and Mario
 * @version 3.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* Private functions */
Status game_actions_unknown(Game *game) { return ERROR; }
Status game_actions_exit(Game *game) { return OK; }
Status game_actions_open(Game *game);
Status game_actions_recruit(Game *game);

Status game_actions_take(Game *game)
{
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Command *cmd = NULL;
  const char *obj_name = NULL;
  Id obj_id = NO_ID;
  Object *obj = NULL;
  Id dependency = NO_ID;
  int i;

  if (!game)
    return ERROR;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  cmd = game_get_last_command(game);
  obj_name = command_get_arg(cmd);

  if (!obj_name || obj_name[0] == '\0')
    return ERROR;

  for (i = 1; i < MAX_OBJECTS; i++)
  {
    Object *o = game_get_object(game, i);
    if (o && strcasecmp(object_get_name(o), obj_name) == 0)
    {
      obj_id = i;
      break;
    }
  }

  if (obj_id == NO_ID || space_has_object(current_space, obj_id) == FALSE)
    return ERROR;

  obj = game_get_object(game, obj_id);

  if (object_get_movable(obj) == FALSE)
  {
    return ERROR;
  }

  dependency = object_get_dependency(obj);
  if (dependency != NO_ID && player_has_object(player, dependency) == FALSE)
  {
    return ERROR;
  }

  if (player_has_object(player, obj_id) == TRUE)
    return ERROR;

  if (player_add_object(player, obj_id) == OK)
  {
    space_del_object(current_space, obj_id);
    return OK;
  }
  return ERROR;
}

Status game_actions_drop(Game *game) {
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Command *cmd = NULL;
  const char *obj_name = NULL;
  Id obj_id = NO_ID;
  Object *obj = NULL;
  int i;

  if (!game) return ERROR;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  cmd = game_get_last_command(game);
  obj_name = command_get_arg(cmd);

  if (!obj_name || obj_name[0] == '\0') return ERROR;

  for (i = 1; i < MAX_OBJECTS; i++) {
    obj = game_get_object(game, i);
    if (obj && strcasecmp(object_get_name(obj), obj_name) == 0) {
      obj_id = i;
      break;
    }
  }

  if (obj_id == NO_ID) return ERROR;
  if (player_has_object(player, obj_id) == FALSE) return ERROR;

  if (player_del_object(player, obj_id) == OK) {
    space_add_object(current_space, obj_id);
    
    for (i = 1; i < MAX_OBJECTS; i++) {
      if (player_has_object(player, i) == TRUE) {
        Object *dep_obj = game_get_object(game, i);
        if (dep_obj && object_get_dependency(dep_obj) == obj_id) {
          player_del_object(player, i);
          space_add_object(current_space, i);
        }
      }
    }

    return OK;
  }
  return ERROR;
}

Status game_actions_move(Game *game)
{
  Id current_id = NO_ID;
  Id dest_id = NO_ID;
  const char *arg = NULL;
  Direction dir = N;

  if (!game)
    return ERROR;

  arg = command_get_arg(game_get_last_command(game));
  if (!arg)
    return ERROR;

  if (strcmp(arg, "north") == 0 || strcmp(arg, "n") == 0)
  {
    dir = N;
  }
  else if (strcmp(arg, "south") == 0 || strcmp(arg, "s") == 0)
  {
    dir = S;
  }
  else if (strcmp(arg, "east") == 0 || strcmp(arg, "e") == 0)
  {
    dir = E;
  }
  else if (strcmp(arg, "west") == 0 || strcmp(arg, "w") == 0)
  {
    dir = W;
  }
  else if (strcmp(arg, "up") == 0 || strcmp(arg, "u") == 0)
  {
    dir = U;
  }
  else if (strcmp(arg, "down") == 0 || strcmp(arg, "d") == 0)
  {
    dir = D;
  }
  else
  {
    return ERROR;
  }

  current_id = game_get_player_location(game);
  if (current_id == NO_ID)
    return ERROR;

  if (game_connection_is_open(game, current_id, dir) == TRUE)
  {
    dest_id = game_get_connection(game, current_id, dir);
    if (dest_id != NO_ID)
    {
      game_set_player_location(game, dest_id);
      return OK;
    }
  }
  return ERROR;
}

Status game_actions_attack(Game *game)
{
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Id char_id = NO_ID;
  Character *c = NULL;
  int roll = 0;

  if (!game)
    return ERROR;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);
  player = game_get_player(game);
  char_id = space_get_character(current_space);

  if (char_id != NO_ID)
  {
    c = game_get_character(game, char_id);
    if (c && character_get_friendly(c) == FALSE)
    {
      roll = rand() % 10;
      if (roll <= 4)
      {
        player_set_health(player, player_get_health(player) - 1);
        if (player_get_health(player) <= 0)
        {
          game_set_finished(game, TRUE);
        }
      }
      else
      {
        character_set_health(c, character_get_health(c) - 1);
        if (character_get_health(c) <= 0)
        {
          space_set_character(current_space, NO_ID);
        }
      }
      return OK;
    }
  }
  return ERROR;
}

Status game_actions_chat(Game *game)
{
  Id p_loc = NO_ID;
  Space *current_space = NULL;
  Id char_id = NO_ID;

  if (!game)
    return ERROR;

  p_loc = game_get_player_location(game);
  current_space = game_get_space(game, p_loc);

  if (!current_space)
    return ERROR;

  char_id = space_get_character(current_space);

  if (char_id != NO_ID)
  {
    return OK;
  }

  return ERROR;
}

Status game_actions_inspect(Game *game)
{
  const char *arg = NULL;
  Command *cmd = NULL;

  if (!game)
    return ERROR;

  cmd = game_get_last_command(game);
  arg = command_get_arg(cmd);

  if (arg && arg[0] != '\0')
  {
    return OK;
  }

  return ERROR;
}

Status game_actions_recruit(Game *game)
{
  Command *cmd = NULL;
  const char *name = NULL;
  Player *player = NULL;
  Id player_id = NO_ID;

  if (!game)
    return ERROR;

  cmd = game_get_last_command(game);
  name = command_get_arg(cmd);
  player = game_get_player(game);
  player_id = player_get_id(player);

  if (!name || name[0] == '\0')
  {
    return ERROR;
  }

  if (game_recruit_character(game, player_id, name) == OK)
  {
    return OK;
  }

  return ERROR;
}

Status game_actions_use(Game *game)
{
  Player *player = NULL;
  Command *cmd = NULL;
  const char *arg = NULL;
  char obj_name[WORD_SIZE] = "";
  char chr_name[WORD_SIZE] = "";
  Id obj_id = NO_ID;
  Object *obj = NULL;
  int i, parsed, health_effect;

  if (!game)
    return ERROR;

  player = game_get_player(game);
  cmd = game_get_last_command(game);
  arg = command_get_arg(cmd);

  if (!arg || arg[0] == '\0')
    return ERROR;

  parsed = sscanf(arg, "%s over %s", obj_name, chr_name);
  if (parsed < 1)
    return ERROR;

  for (i = 1; i < MAX_OBJECTS; i++)
  {
    obj = game_get_object(game, i);
    if (obj && strcasecmp(object_get_name(obj), obj_name) == 0)
    {
      obj_id = i;
      break;
    }
  }

  if (obj_id == NO_ID)
    return ERROR;

  if (player_has_object(player, obj_id) == FALSE)
    return ERROR;

  health_effect = object_get_health(obj);
  if (health_effect == 0)
    return ERROR;

  if (parsed == 1)
  {

    player_set_health(player, player_get_health(player) + health_effect);
  }
  else if (parsed == 2)
  {

    Id char_id = NO_ID;
    Character *c = NULL;

    for (i = 1; i < MAX_CHARACTERS; i++)
    {
      c = game_get_character(game, i);
      if (c && strcasecmp(character_get_name(c), chr_name) == 0)
      {
        char_id = i;
        break;
      }
    }
    if (char_id == NO_ID)
      return ERROR;

    if (character_get_following(c) != player_get_id(player))
      return ERROR;

    character_set_health(c, character_get_health(c) + health_effect);
  }

  player_del_object(player, obj_id);

  return OK;
}

Status game_actions_open(Game *game)
{
  Player *player = NULL;
  Command *cmd = NULL;
  const char *arg = NULL;
  char lnk_name[WORD_SIZE] = "";
  char obj_name[WORD_SIZE] = "";
  Id obj_id = NO_ID;
  Id lnk_id = NO_ID;
  Object *obj = NULL;
  Link *lnk = NULL;
  int i, parsed;

  if (!game)
    return ERROR;

  player = game_get_player(game);
  cmd = game_get_last_command(game);
  arg = command_get_arg(cmd);

  if (!arg || arg[0] == '\0')
    return ERROR;

  parsed = sscanf(arg, "%s with %s", lnk_name, obj_name);
  if (parsed != 2)
    return ERROR;

  for (i = 1; i < MAX_OBJECTS; i++)
  {
    obj = game_get_object(game, i);
    if (obj && strcasecmp(object_get_name(obj), obj_name) == 0)
    {
      obj_id = i;
      break;
    }
  }
  if (obj_id == NO_ID)
    return ERROR;

  for (i = 1; i < MAX_LINKS; i++)
  {
    lnk = game_get_link(game, i);
    if (lnk && strcasecmp(link_get_name(lnk), lnk_name) == 0)
    {
      lnk_id = i;
      break;
    }
  }
  if (lnk_id == NO_ID)
    return ERROR;

  if (player_has_object(player, obj_id) == FALSE)
    return ERROR;

  if (object_get_open(obj) != lnk_id)
    return ERROR;

  if (link_set_open(lnk, TRUE) == OK)
  {
    return OK;
  }

  return ERROR;
}

Status game_actions_update(Game *game, Command *command)
{
  CommandCode cmd;
  Status status = OK;

  if (!game || !command)
    return ERROR;

  game_set_last_command(game, command);
  cmd = command_get_code(command);

  switch (cmd)
  {
  case UNKNOWN:
    status = game_actions_unknown(game);
    break;
  case EXIT:
    status = game_actions_exit(game);
    break;
  case MOVE:
    status = game_actions_move(game);
    break;
  case TAKE:
    status = game_actions_take(game);
    break;
  case DROP:
    status = game_actions_drop(game);
    break;
  case ATTACK:
    status = game_actions_attack(game);
    break;
  case INSPECT:
    status = game_actions_inspect(game);
    break;
  case CHAT:
    status = game_actions_chat(game);
    break;
  case RECRUIT:
    status = game_actions_recruit(game);
    break;
  case USE:
    status = game_actions_use(game);
    break;
  case OPEN:
    status = game_actions_open(game);
    break;
  default:
    break;
  }

  return status;
}