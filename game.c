/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Mario
 * @version 2.0
 * @date 26-02-2026
 * @copyright GNU Public License
 */

#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Game
 *
 * This struct stores all the information of the game.
 */
struct _Game
{
  Player *player;                        /*!< Pointer to the player of the game */
  Object *objects[MAX_OBJECTS];          /*!< Array of pointers to the objects of the game */
  int n_objects;                         /*!< Number of objects in the game */
  Character *characters[MAX_CHARACTERS]; /*!< Array of pointers to characters */
  int n_characters;                      /*!< Number of characters in the game */
  Space *spaces[MAX_SPACES];             /*!< Array of pointers to the spaces of the game */
  int n_spaces;                          /*!< Number of spaces in the game */
  Link *links[MAX_LINKS];                /*!< Array of pointers to the links of the game */
  int n_links;                           /*!< Number of links in the game */
  Command *last_cmd;                     /*!< Last command executed in the game */
  Bool finished;                         /*!< Whether the game is finished or not */
};

Status game_create(Game **game)
{
  int i;
  Game *newGame = NULL;

  if (!game)
    return ERROR;

  newGame = (Game *)calloc(1, sizeof(Game));
  if (newGame == NULL)
  {
    return ERROR;
  }

  for (i = 0; i < MAX_SPACES; i++)
  {
    newGame->spaces[i] = NULL;
  }
  newGame->n_spaces = 0;

  for (i = 0; i < MAX_OBJECTS; i++)
  {
    newGame->objects[i] = NULL;
  }
  newGame->n_objects = 0;

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    newGame->characters[i] = NULL;
  }
  newGame->n_characters = 0;

  for (i = 0; i < MAX_LINKS; i++)
  {
    newGame->links[i] = NULL;
  }
  newGame->n_links = 0;

  newGame->player = player_create(1);
  if (newGame->player == NULL)
  {
    free(newGame);
    return ERROR;
  }

  player_set_gdesc(newGame->player, "^O^");

  newGame->last_cmd = command_create();
  if (newGame->last_cmd == NULL)
  {
    player_destroy(newGame->player);
    free(newGame);
    return ERROR;
  }

  newGame->finished = FALSE;
  *game = newGame;

  return OK;
}

Status game_destroy(Game *game)
{
  int i = 0;

  if (!game)
    return ERROR;

  for (i = 0; i < game->n_spaces; i++)
  {
    space_destroy(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++)
  {
    object_destroy(game->objects[i]);
  }

  for (i = 0; i < game->n_characters; i++)
  {
    character_destroy(game->characters[i]);
  }

  for (i = 0; i < game->n_links; i++)
  {
    link_destroy(game->links[i]);
  }

  player_destroy(game->player);
  command_destroy(game->last_cmd);

  free(game);

  return OK;
}

Status game_add_space(Game *game, Space *space)
{
  if (!game || !space || game->n_spaces >= MAX_SPACES)
  {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Status game_add_object(Game *game, Object *object)
{
  if (!game || !object || game->n_objects >= MAX_OBJECTS)
  {
    return ERROR;
  }

  game->objects[game->n_objects] = object;
  game->n_objects++;

  return OK;
}

Status game_add_character(Game *game, Character *character)
{
  if (!game || !character || game->n_characters >= MAX_CHARACTERS)
  {
    return ERROR;
  }

  game->characters[game->n_characters] = character;
  game->n_characters++;

  return OK;
}

Status game_add_link(Game *game, Link *link)
{
  if (!game || !link || game->n_links >= MAX_LINKS)
  {
    return ERROR;
  }

  game->links[game->n_links] = link;
  game->n_links++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position)
{
  if (!game || position < 0 || position >= game->n_spaces)
  {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

Space *game_get_space(Game *game, Id id)
{
  int i = 0;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (id == space_get_id(game->spaces[i]))
    {
      return game->spaces[i];
    }
  }

  return NULL;
}

Player *game_get_player(Game *game)
{
  if (!game)
    return NULL;
  return game->player;
}

Status game_set_player(Game *game, Player *player)
{
  if (!game || !player)
    return ERROR;
  if (game->player != NULL)
  {
    player_destroy(game->player);
  }

  game->player = player;
  return OK;
}

Status game_set_player(Game *game, Player *player)
{
  if (!game || !player)
    return ERROR;
  if (game->player != NULL)
  {
    player_destroy(game->player);
  }

  game->player = player;
  return OK;
}

Object *game_get_object(Game *game, Id id)
{
  int i;
  if (!game || id == NO_ID)
    return NULL;

  for (i = 0; i < game->n_objects; i++)
  {
    if (object_get_id(game->objects[i]) == id)
    {
      return game->objects[i];
    }
  }
  return NULL;
}

Character *game_get_character(Game *game, Id id)
{
  int i;
  if (!game || id == NO_ID)
    return NULL;

  for (i = 0; i < game->n_characters; i++)
  {
    if (character_get_id(game->characters[i]) == id)
    {
      return game->characters[i];
    }
  }
  return NULL;
}

Link *game_get_link(Game *game, Id id)
{
  int i = 0;

  if (!game || id == NO_ID)
  {
    return NULL;
  }

  for (i = 0; i < game->n_links; i++)
  {
    if (id == link_get_id(game->links[i]))
    {
      return game->links[i];
    }
  }

  return NULL;
}

Id game_get_connection(Game *game, Id space, Direction dir)
{
  int i = 0;
  Id origin = NO_ID;
  Direction link_dir = N;

  if (game == NULL || space == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++)
  {
    origin = link_get_origin(game->links[i]);
    link_dir = link_get_direction(game->links[i]);

    if (origin == space && link_dir == dir)
    {
      return link_get_destination(game->links[i]);
    }
  }

  return NO_ID;
}

Bool game_connection_is_open(Game *game, Id space, Direction dir)
{
  int i = 0;
  Id origin = NO_ID;
  Direction link_dir = N;

  if (game == NULL || space == NO_ID)
  {
    return FALSE;
  }

  for (i = 0; i < game->n_links; i++)
  {
    origin = link_get_origin(game->links[i]);
    link_dir = link_get_direction(game->links[i]);

    if (origin == space && link_dir == dir)
    {
      return link_get_open(game->links[i]);
    }
  }

  return FALSE;
}

Id game_get_player_location(Game *game)
{
  if (!game)
    return NO_ID;
  return player_get_location(game->player);
}

Status game_set_player_location(Game *game, Id id)
{
  Space *space = NULL;

  if (!game || id == NO_ID)
  {
    return ERROR;
  }

  if (player_set_location(game->player, id) == OK)
  {

    space = game_get_space(game, id);
    if (space)
    {
      space_set_discovered(space, TRUE);
    }
    return OK;
  }

  return ERROR;
}

Id game_get_object_location(Game *game, Id object_id)
{
  int i;

  if (!game || object_id == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_has_object(game->spaces[i], object_id) == TRUE)
    {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_object_location(Game *game, Id space_id, Id object_id)
{
  Id current_space_id = NO_ID;
  Space *current_space = NULL;
  Space *new_space = NULL;

  if (!game || object_id == NO_ID)
  {
    return ERROR;
  }

  /* Remove from current location if any */
  current_space_id = game_get_object_location(game, object_id);
  if (current_space_id != NO_ID)
  {
    current_space = game_get_space(game, current_space_id);
    space_del_object(current_space, object_id);
  }

  /* Place in new location */
  if (space_id != NO_ID)
  {
    new_space = game_get_space(game, space_id);
    if (new_space)
    {
      space_add_object(new_space, object_id);
    }
  }

  return OK;
}

Id game_get_character_location(Game *game, Id char_id)
{
  int i;

  if (!game || char_id == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_spaces; i++)
  {
    if (space_get_character(game->spaces[i]) == char_id)
    {
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}

Status game_set_character_location(Game *game, Id space_id, Id char_id)
{
  Id current_space_id = NO_ID;
  Space *current_space = NULL;
  Space *new_space = NULL;

  if (!game || char_id == NO_ID)
  {
    return ERROR;
  }

  /* Remove from current location */
  current_space_id = game_get_character_location(game, char_id);
  if (current_space_id != NO_ID)
  {
    current_space = game_get_space(game, current_space_id);
    space_set_character(current_space, NO_ID);
  }

  /* Place in new location */
  if (space_id != NO_ID)
  {
    new_space = game_get_space(game, space_id);
    if (new_space)
    {
      space_set_character(new_space, char_id);
    }
  }

  return OK;
}

Command *game_get_last_command(Game *game)
{
  if (!game)
    return NULL;
  return game->last_cmd;
}

Status game_set_last_command(Game *game, Command *command)
{
  if (!game)
    return ERROR;
  game->last_cmd = command;
  return OK;
}

Bool game_get_finished(Game *game)
{
  if (!game)
    return FALSE;
  return game->finished;
}

Status game_set_finished(Game *game, Bool finished)
{
  if (!game)
    return ERROR;
  game->finished = finished;
  return OK;
}

void game_print(Game *game)
{
  int i = 0;

  if (!game)
    return;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++)
  {
    space_print(game->spaces[i]);
  }

  printf("=> Objects info: \n");
  for (i = 0; i < game->n_objects; i++)
  {
    object_print(game->objects[i]);
  }

  printf("=> Characters info: \n");
  for (i = 0; i < game->n_characters; i++)
  {
    character_print(game->characters[i]);
  }

  printf("=> Player info: \n");
  player_print(game->player);

  printf("=> Links info: \n");
  for (i = 0; i < game->n_links; i++)
  {
    link_print(game->links[i]);
  }
}

Status game_set_space_discovered(Game *game, Id space_id, Bool discovered)
{
  Space *space = game_get_space(game, space_id);
  if (!space)
    return ERROR;
  return space_set_discovered(space, discovered);
}

Bool game_get_space_discovered(Game *game, Id space_id)
{
  Space *space = game_get_space(game, space_id);
  if (!space)
    return FALSE;
  return space_get_discovered(space);
}

Id game_get_connection(Game *game, Id space_id, Direction dir)
{
  int i;
  Link *link = NULL;

  if (!game || space_id == NO_ID)
  {
    return NO_ID;
  }

  for (i = 0; i < game->n_links; i++)
  {
    link = game->links[i];

    if (link != NULL && link_get_origin(link) == space_id && link_get_direction(link) == dir)
    {

      /* ...comprobamos si está abierto */
      if (link_get_status(link) == TRUE)
      {
        return link_get_destination(link);
      }
      else
      {

        return NO_ID;
      }
    }
  }

  return NO_ID;
}