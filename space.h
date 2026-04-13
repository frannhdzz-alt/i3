/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 08-04-2026
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

typedef struct _Space Space;

/**
 * @brief It creates a new space, allocating memory and initializing its members
 * @author Rodrigo
 *
 * @param id the identification number for the new space
 * @return a new space, initialized
 */
Space *space_create(Id id);

/**
 * @brief It destroys a space, freeing the allocated memory
 * @author Rodrigo
 *
 * @param space a pointer to the space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space *space);

/**
 * @brief It gets the id of a space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return the id of space
 */
Id space_get_id(Space *space);

/**
 * @brief It sets the name of a space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space *space, char *name);

/**
 * @brief It gets the name of a space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return  a string with the name of the space
 */
const char *space_get_name(Space *space);

/**
 * @brief It adds an object to the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param id the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space *space, Id id);

/**
 * @brief It deletes an object from the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param id the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_del_object(Space *space, Id id);

/**
 * @brief It checks if an object is in the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param id the id of the object
 * @return TRUE if the object is in the space, FALSE otherwise
 */
Bool space_has_object(Space *space, Id id);

/**
 * @brief It gets the set of objects in the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return A pointer to the set of objects
 */
Set *space_get_objects(Space *space);

/**
 * @brief It sets the character in the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param id the id of the character
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_character(Space *space, Id id);

/**
 * @brief It gets the character in the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return the id of the character in the space
 */
Id space_get_character(Space *space);

/**
 * @brief It sets a line of the graphic description of the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param line the line number (0 to 4)
 * @param gdesc the string with the graphic description (max 9 chars)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_gdesc(Space *space, int line, char *gdesc);

/**
 * @brief It gets a line of the graphic description of the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param line the line number (0 to 4)
 * @return a string with the graphic description line
 */
const char *space_get_gdesc(Space *space, int line);

/**
 * @brief It prints the space information
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);
/**
 * @brief It sets the discovered status of the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @param discovered the new discovered status (TRUE or FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space* space, Bool discovered);

/**
 * @brief It gets the discovered status of the space
 * @author Rodrigo
 *
 * @param space a pointer to the space
 * @return TRUE if discovered, FALSE otherwise
 */
Bool space_get_discovered(Space* space);

#endif