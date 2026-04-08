/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author María Gómez
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Link {
    Id id;
    char name[MAX_NAME];
    Id origin;
    Id destination;
    Direction direction;
    Bool open;
};

Link* link_create(Id id) {
  Link *newLink = NULL;
  if (id == NO_ID) return NULL;
  newLink = (Link*) calloc(1, sizeof(Link));
  if (newLink == NULL) return NULL;
  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = N;
  newLink->open = TRUE;
  return newLink;
}

Status link_destroy(Link* link) {
  if (!link) return ERROR;
  free(link);
  return OK;
}

Id link_get_id(Link* link) {
  if (!link) return NO_ID;
  return link->id;
}

Status link_set_name(Link* link, char* name) {
  if (!link || !name) return ERROR;
  if (!strcpy(link->name, name)) return ERROR;
  return OK;
}

const char* link_get_name(Link* link) {
  if (!link) return NULL;
  return link->name;
}

Status link_print(Link* link) {
  if (!link) return ERROR;
  fprintf(stdout, "--> Link (Id: %ld; Name: %s)\n", link->id, link->name);
  return OK;
}