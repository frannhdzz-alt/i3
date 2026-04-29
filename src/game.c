/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Mario
 * @version 3.0
 * @date 13-04-2026
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
  Player *players[2];                    /*!< Array of pointers to the players of the game */
  int turn;                              /*!< Current turn (0 or 1) */
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

  newGame->players[0] = NULL;
  newGame->players[1] = NULL;
  newGame->turn = 0;

  newGame->last_cmd = command_create();
  if (newGame->last_cmd == NULL)
  {
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


  for (i = 0; i < 2; i++)
  {
    if (game->players[i] != NULL)
    {
      player_destroy(game->players[i]);
    }
  }

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


Player *game_get_active_player(Game *game)
{
  if (game == NULL) return NULL;
  
  return game->players[game->turn];
}

Status game_add_player(Game *game, Player *player)
{
  int i;

  if (game == NULL || player == NULL)
  {
    return ERROR;
  }


  for (i = 0; i < 2; i++)
  {
    if (game->players[i] == NULL)
    {
      game->players[i] = player;
      return OK;
    }
  }

  return ERROR; 
}

Player *game_get_player(Game *game)
{
  if (!game)
    return NULL;
  return game_get_active_player(game);
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
  return player_get_location(game_get_active_player(game));
}

Status game_set_player_location(Game *game, Id id)
{
  Space *space = NULL;

  if (!game || id == NO_ID)
  {
    return ERROR;
  }

  if (player_set_location(game_get_active_player(game), id) == OK)
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


  current_space_id = game_get_object_location(game, object_id);
  if (current_space_id != NO_ID)
  {
    current_space = game_get_space(game, current_space_id);
    space_del_object(current_space, object_id);
  }


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


  current_space_id = game_get_character_location(game, char_id);
  if (current_space_id != NO_ID)
  {
    current_space = game_get_space(game, current_space_id);
    space_set_character(current_space, NO_ID);
  }


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
  player_print(game_get_active_player(game));

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
      if (link_get_open(link) == TRUE)
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

Status game_next_turn(Game *game)
{
  if (game == NULL) {
    return ERROR;
  }

  if (game->turn == 0) {
    game->turn = 1;
  } else {
    game->turn = 0;
  }

  return OK;
}

Character* game_get_character_by_name(Game *game, const char *name) {
  int i;
  Character *c = NULL;

  if (!game || !name) return NULL;

  for (i = 0; i < game->n_characters; i++) {
    c = game->characters[i];
    if (c && strcmp(character_get_name(c), name) == 0) {
      return c;
    }
  }
  return NULL;
}

Status game_recruit_character(Game *game, Id player_id, const char *char_name) {
  Character *c = NULL;

  if (!game || player_id == NO_ID || !char_name) return ERROR;

  c = game_get_character_by_name(game, char_name);
  if (!c) return ERROR;

  /* Solo personajes amigos */
  if (character_get_friendly(c) == FALSE) return ERROR;

  /* Asignar follower */
  return character_set_following(c, player_id);
}

Status game_abandon_character(Game *game, Id player_id, const char *char_name) {
    Character *c = NULL;

    if (!game || player_id == NO_ID || !char_name) return ERROR;

    c = game_get_character_by_name(game, char_name);
    if (!c) return ERROR;

    /* Solo se puede abandonar si realmente seguía al jugador */
    if (character_get_following(c) != player_id) return ERROR;

    /* Dejar de seguir */
    return character_set_following(c, NO_ID);
}

int game_count_followers(Game *game, Id player_id) {
    int i, count = 0;
    Character *c = NULL;

    if (!game || player_id == NO_ID) return 0;

    for (i = 0; i < game->n_characters; i++) {
        c = game->characters[i];
        if (c && character_get_following(c) == player_id) {
            count++;
        }
    }
    return count;
}

Character* game_get_follower_by_index(Game *game, Id player_id, int index) {
    int i, count = 0;
    Character *c = NULL;

    for (i = 0; i < game->n_characters; i++) {
        c = game->characters[i];
        if (c && character_get_following(c) == player_id) {
            if (count == index) return c;
            count++;
        }
    }
    return NULL;
}

