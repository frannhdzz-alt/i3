/**
 * @brief It implements the set module
 *
 * @file set.c
 * @author Rodrigo
 * @version 1.0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Set
 *
 * This struct stores an array of ids and the current number of ids.
 */
struct _Set {
  Id ids[MAX_IDS]; /*!< Array to store the identifiers */
  int n_ids;       /*!< Number of identifiers currently in the set */
};

Set* set_create() {
  Set* newSet = NULL;
  int i;

  newSet = (Set*)calloc(1, sizeof(Set));
  if (newSet == NULL) {
    return NULL;
  }

  newSet->n_ids = 0;
  for (i = 0; i < MAX_IDS; i++) {
    newSet->ids[i] = NO_ID;
  }

  return newSet;
}

Status set_destroy(Set* set) {
  if (!set) {
    return ERROR;
  }

  free(set);
  return OK;
}

Status set_add(Set* set, Id id) {
  if (!set || id == NO_ID || set->n_ids >= MAX_IDS) {
    return ERROR;
  }

  /* Check if the id is already in the set */
  if (set_find(set, id) == TRUE) {
    return ERROR;
  }

  set->ids[set->n_ids] = id;
  set->n_ids++;

  return OK;
}

Status set_del(Set* set, Id id) {
  int i, j;

  if (!set || id == NO_ID) {
    return ERROR;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      /* Shift elements to the left to close the gap */
      for (j = i; j < set->n_ids - 1; j++) {
        set->ids[j] = set->ids[j + 1];
      }
      set->ids[set->n_ids - 1] = NO_ID;
      set->n_ids--;
      return OK;
    }
  }

  return ERROR; /* Id not found */
}

Bool set_find(Set* set, Id id) {
  int i;

  if (!set || id == NO_ID) {
    return FALSE;
  }

  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      return TRUE;
    }
  }

  return FALSE;
}

Status set_print(Set* set) {
  int i;

  if (!set) {
    return ERROR;
  }

  fprintf(stdout, "--> Set (Elements: %d)\n", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    fprintf(stdout, "---> Id: %ld\n", set->ids[i]);
  }

  return OK;
}

int set_get_n_ids(Set *set) {
    if (!set) return 0;
    return set->n_ids;
}

Id set_get_id_at(Set *set, int index) {
  if (!set || index < 0 || index >= set->n_ids) {
    return NO_ID;
  }
  return set->ids[index];
}