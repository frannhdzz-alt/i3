/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Rodrigo
 * @version 1.0
 * @date 04-02-2025
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

#endif