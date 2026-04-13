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
  Id id;                    /*!< Object identifier */
  char name[WORD_SIZE + 1]; /*!< Object name */
  char description[WORD_SIZE + 1]; /*!< Object description */
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

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

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