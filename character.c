/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Mario
 * @version 1.0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Character
 *
 * This struct stores all the information of a character.
 */
struct _Character {
  Id id;                    /*!< Character identifier */
  char name[WORD_SIZE + 1]; /*!< Character name */
  char gdesc[7];            /*!< Character graphic description (6 chars + \0) */
  int health;               /*!< Character health points */
  Bool friendly;            /*!< Character friendliness */
  char message[WORD_SIZE + 2]; /*!< Character message */
};

Character* character_create(Id id) {
  Character* newCharacter = NULL;

  if (id == NO_ID) return NULL;

  newCharacter = (Character*)calloc(1, sizeof(Character));
  if (newCharacter == NULL) {
    return NULL;
  }

  newCharacter->id = id;
  newCharacter->name[0] = '\0';
  newCharacter->gdesc[0] = '\0';
  newCharacter->health = 0;
  newCharacter->friendly = FALSE;
  newCharacter->message[0] = '\0';

  return newCharacter;
}

Status character_destroy(Character* character) {
  if (!character) {
    return ERROR;
  }

  free(character);
  return OK;
}

Id character_get_id(Character* character) {
  if (!character) {
    return NO_ID;
  }
  return character->id;
}

Status character_set_name(Character* character, char* name) {
  if (!character || !name) {
    return ERROR;
  }

  if (!strcpy(character->name, name)) {
    return ERROR;
  }

  return OK;
}

const char* character_get_name(Character* character) {
  if (!character) {
    return NULL;
  }
  return character->name;
}

Status character_set_gdesc(Character* character, char* gdesc) {
  if (!character || !gdesc) {
    return ERROR;
  }

  strncpy(character->gdesc, gdesc, 6);
  character->gdesc[6] = '\0';

  return OK;
}

const char* character_get_gdesc(Character* character) {
  if (!character) {
    return NULL;
  }
  return character->gdesc;
}

Status character_set_health(Character* character, int health) {
  if (!character || health < 0) {
    return ERROR;
  }

  character->health = health;
  return OK;
}

int character_get_health(Character* character) {
  if (!character) {
    return -1;
  }
  return character->health;
}

Status character_set_friendly(Character* character, Bool friendly) {
  if (!character) {
    return ERROR;
  }

  character->friendly = friendly;
  return OK;
}

Bool character_get_friendly(Character* character) {
  if (!character) {
    return FALSE; 
  }
  return character->friendly;
}

Status character_set_message(Character* character, char* message) {
  if (!character || !message) {
    return ERROR;
  }

  if (!strcpy(character->message, message)) {
    return ERROR;
  }

  return OK;
}

const char* character_get_message(Character* character) {
  if (!character) {
    return NULL;
  }
  return character->message;
}

Status character_print(Character* character) {
  if (!character) {
    return ERROR;
  }

  fprintf(stdout, "--> Character (Id: %ld; Name: %s)\n", character->id, character->name);
  fprintf(stdout, "---> Graphic Description: %s\n", character->gdesc);
  fprintf(stdout, "---> Health: %d\n", character->health);
  fprintf(stdout, "---> Friendly: %s\n", character->friendly == TRUE ? "TRUE" : "FALSE");
  fprintf(stdout, "---> Message: %s\n", character->message);

  return OK;
}