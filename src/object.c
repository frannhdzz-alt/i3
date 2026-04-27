/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Rodrigo
 * @version 1.0
 * @date 05-04-2025
 * @copyright GNU Public License
 */

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Object
 *
 * This struct stores all the information of an object.
 */
struct _Object {
  Id id;                            /*!< Object identifier */
  char name[WORD_SIZE + 1];         /*!< Object name */
  char description[WORD_SIZE + 1];  /*!< Object description */
  int health;                       /*!< Points of health the object gives/takes */
  Bool movable;                     /*!< TRUE if the object can be moved */
  Id dependency;                    /*!< Id of the object required to take this one */
  Id open;                          /*!< Id of the link this object can open */
};

Object* object_create(Id id) {
  Object* newObject = NULL;

  if (id == NO_ID) return NULL;

  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

  newObject->id = id;
  newObject->name[0] = '\0';
  newObject->health = 0;
  newObject->movable = FALSE;
  newObject->dependency = NO_ID;
  newObject->open = NO_ID;

  return newObject;
}

Status object_destroy(Object* object) {
  if (!object) {
    return ERROR;
  }

  free(object);
  return OK;
}

Id object_get_id(Object* object) {
  if (!object) {
    return NO_ID;
  }
  return object->id;
}

Status object_set_name(Object* object, char* name) {
  if (!object || !name) {
    return ERROR;
  }

  if (!strcpy(object->name, name)) {
    return ERROR;
  }

  return OK;
}

const char* object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}

Status object_print(Object* object) {
  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Health: %d; Movable: %d; Dependency: %ld; Open: %ld)\n", 
          object->id, object->name, object->health, object->movable, object->dependency, object->open);

  return OK;
}

Status object_set_description(Object* object, char* desc) {
  if (!object || !desc) return ERROR;
  if (!strcpy(object->description, desc)) return ERROR;
  return OK;
}

const char* object_get_description(Object* object) {
  if (!object) return NULL;
  return object->description;
}

Status object_set_health(Object* object, int health) {
  if (!object) return ERROR;
  object->health = health;
  return OK;
}

int object_get_health(Object* object) {
  if (!object) return 0;
  return object->health;
}

Status object_set_movable(Object* object, Bool movable) {
  if (!object) return ERROR;
  object->movable = movable;
  return OK;
}

Bool object_get_movable(Object* object) {
  if (!object) return FALSE;
  return object->movable;
}

Status object_set_dependency(Object* object, Id dependency) {
  if (!object) return ERROR;
  object->dependency = dependency;
  return OK;
}

Id object_get_dependency(Object* object) {
  if (!object) return NO_ID;
  return object->dependency;
}

Status object_set_open(Object* object, Id open) {
  if (!object) return ERROR;
  object->open = open;
  return OK;
}

Id object_get_open(Object* object) {
  if (!object) return NO_ID;
  return object->open;
}