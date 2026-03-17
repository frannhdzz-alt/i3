/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author Rodrigo 
 * @version 1.0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_IDS 100 

typedef struct _Set Set;

/**
 * @brief It creates a new set
 * @author Rodrigo
 *
 * @return A new set, initialized, or NULL if there was an error
 */
Set* set_create();

/**
 * @brief It destroys a set
 * @author Rodrigo
 *
 * @param set A pointer to the set to be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_destroy(Set* set);

/**
 * @brief It adds a new id to the set
 * @author Rodrigo
 *
 * @param set A pointer to the set
 * @param id The id to be added
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_add(Set* set, Id id);

/**
 * @brief It removes an id from the set
 * @author Rodrigo
 *
 * @param set A pointer to the set
 * @param id The id to be removed
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_del(Set* set, Id id);

/**
 * @brief It checks if an id is inside the set
 * @author Rodrigo
 *
 * @param set A pointer to the set
 * @param id The id to find
 * @return TRUE if the id is in the set, FALSE otherwise
 */
Bool set_find(Set* set, Id id);

/**
 * @brief It prints the set information
 * @author Rodrigo
 *
 * @param set A pointer to the set
 * @return OK if everything goes well, ERROR otherwise
 */
Status set_print(Set* set);

#endif