/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Mario
 * @version 3.0
 * @date 24-03-2026
 */

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                    /*!< Player identifier */
  char name[WORD_SIZE + 1]; /*!< Player name */
  Id location;              /*!< Id of the space where the player is */
  Inventory* backpack;      /*!< Player inventory (replaces object field) */
  int health;               /*!< Player health points */
  char gdesc[7];            /*!< Player graphic description (6 chars + \0) */
};

Player* player_create(Id id) {
  Player* newPlayer = NULL;

  if (id == NO_ID) return NULL;

  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->health = 5;
  newPlayer->gdesc[0] = '\0';

  /* Create backpack with capacity 5 */
  newPlayer->backpack = inventory_create(5);
  if (!newPlayer->backpack) {
    free(newPlayer);
    return NULL;
  }

  return newPlayer;
}

Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  inventory_destroy(player->backpack);
  free(player);

  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Status player_set_location(Player* player, Id id) {
  if (!player) {
    return ERROR;
  }
  player->location = id;
  return OK;
}

Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/* === INVENTORY FUNCTIONS === */

Status player_add_object(Player* player, Id id) {
  if (!player) {
    return ERROR;
  }
  return inventory_add_object(player->backpack, id);
}

Status player_del_object(Player* player, Id id) {
  if (!player) {
    return ERROR;
  }
  return inventory_del_object(player->backpack, id);
}

Bool player_has_object(Player* player, Id id) {
  if (!player) {
    return FALSE;
  }
  return inventory_has_object(player->backpack, id);
}

Inventory* player_get_inventory(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->backpack;
}

/* === HEALTH & GDESC === */

Status player_set_health(Player* player, int health) {
  if (!player || health < 0) {
    return ERROR;
  }
  player->health = health;
  return OK;
}

int player_get_health(Player* player) {
  if (!player) {
    return -1;
  }
  return player->health;
}

Status player_set_gdesc(Player* player, char* gdesc) {
  if (!player || !gdesc) {
    return ERROR;
  }
  strncpy(player->gdesc, gdesc, 6);
  player->gdesc[6] = '\0';
  return OK;
}

const char* player_get_gdesc(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->gdesc;
}

Status player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);
  fprintf(stdout, "---> Location: %ld\n", player->location);
  fprintf(stdout, "---> Health: %d\n", player->health);
  fprintf(stdout, "---> Graphic Description: %s\n", player->gdesc);

  fprintf(stdout, "---> Backpack:\n");
  inventory_print(player->backpack);

  return OK;
}