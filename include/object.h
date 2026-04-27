/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Rodrigo
 * @version 1.0
 * @date 04-04-2025
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/**
 * @brief It creates a new object
 * @author Rodrigo
 *
 * @param id The identification number for the new object
 * @return A new object, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destroys an object
 * @author Rodrigo
 *
 * @param object A pointer to the object to be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_destroy(Object* object);

/**
 * @brief It gets the id of an object
 * @author Rodrigo
 *
 * @param object A pointer to the object
 * @return The object id
 */
Id object_get_id(Object* object);

/**
 * @brief It sets the name of an object
 * @author Rodrigo
 *
 * @param object A pointer to the object
 * @param name A string with the name to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of an object
 * @author Rodrigo
 *
 * @param object A pointer to the object
 * @return A string with the name of the object
 */
const char* object_get_name(Object* object);

/**
 * @brief It prints the object information
 * @author Rodrigo
 *
 * @param object A pointer to the object
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_print(Object* object);

/**
 * @brief It sets the description of an object
 * @author Rodrigo 
 *
 * @param object A pointer to the object
 * @param desc A string with the description to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_description(Object* object, char* desc);

/**
 * @brief It gets the description of an object
 * @author Rodrigo
 *
 * @param object A pointer to the object
 * @return A string with the description of the object, or NULL if error
 */
const char* object_get_description(Object* object);

/**
 * @brief It sets the health value of an object
 *
 * @param object A pointer to the object
 * @param health The health points to add/subtract
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_health(Object* object, int health);

/**
 * @brief It gets the health value of an object
 *
 * @param object A pointer to the object
 * @return The health points of the object
 */
int object_get_health(Object* object);

/**
 * @brief It sets if an object is movable
 *
 * @param object A pointer to the object
 * @param movable TRUE if it can be moved, FALSE otherwise
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_movable(Object* object, Bool movable);

/**
 * @brief It gets if an object is movable
 *
 * @param object A pointer to the object
 * @return TRUE if it can be moved, FALSE otherwise
 */
Bool object_get_movable(Object* object);

/**
 * @brief It sets the dependency of an object
 *
 * @param object A pointer to the object
 * @param dependency The id of the object it depends on
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_dependency(Object* object, Id dependency);

/**
 * @brief It gets the dependency of an object
 *
 * @param object A pointer to the object
 * @return The id of the object it depends on, or NO_ID
 */
Id object_get_dependency(Object* object);

/**
 * @brief It sets the link id an object can open
 *
 * @param object A pointer to the object
 * @param open The id of the link it opens
 * @return OK if everything goes well, ERROR otherwise
 */
Status object_set_open(Object* object, Id open);

/**
 * @brief It gets the link id an object can open
 *
 * @param object A pointer to the object
 * @return The id of the link it opens, or NO_ID
 */
Id object_get_open(Object* object);

#endif