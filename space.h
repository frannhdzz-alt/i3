/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 07-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set* objects;             /*!< Set of object ids in the space */
  Id character;             /*!< Id of the character in the space */
  char gdesc[5][10];        /*!< Graphic description (5 lines of 9 chars + \0) */
};

Space* space_create(Id id) {
  Space* newSpace = NULL;
  int i;

  if (id == NO_ID) return NULL;

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  
  newSpace->objects = set_create();
  newSpace->character = NO_ID;

  /* Initialize graphic description with spaces */
  for (i = 0; i < 5; i++) {
    strcpy(newSpace->gdesc[i], "         ");
  }

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);
  free(space);
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}

Status space_add_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  return set_add(space->objects, id);
}

Status space_del_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  return set_del(space->objects, id);
}

Bool space_has_object(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return FALSE;
  }
  return set_find(space->objects, id);
}

Set* space_get_objects(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->objects;
}

Status space_set_character(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->character = id;
  return OK;
}

Id space_get_character(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->character;
}

Status space_set_gdesc(Space* space, int line, char* gdesc) {
  if (!space || !gdesc || line < 0 || line > 4) {
    return ERROR;
  }
  strncpy(space->gdesc[line], gdesc, 9);
  space->gdesc[line][9] = '\0';
  return OK;
}

const char* space_get_gdesc(Space* space, int line) {
  if (!space || line < 0 || line > 4) {
    return NULL;
  }
  return space->gdesc[line];
}

Status space_print(Space* space) {
  Id idaux = NO_ID;
  int i;

  if (!space) {
    return ERROR;
  }

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  idaux = space_get_north(space);
  fprintf(stdout, "---> North link: %ld.\n", idaux);
  
  idaux = space_get_south(space);
  fprintf(stdout, "---> South link: %ld.\n", idaux);
  
  idaux = space_get_east(space);
  fprintf(stdout, "---> East link: %ld.\n", idaux);
  
  idaux = space_get_west(space);
  fprintf(stdout, "---> West link: %ld.\n", idaux);

  fprintf(stdout, "---> Objects in the space:\n");
  set_print(space->objects);

  idaux = space_get_character(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> Character in the space: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No character in the space.\n");
  }

  fprintf(stdout, "---> Graphic description:\n");
  for (i = 0; i < 5; i++) {
    fprintf(stdout, "     %s\n", space->gdesc[i]);
  }

  return OK;
}