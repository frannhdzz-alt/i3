/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author María Gómez
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H
#define MAX_NAME 50
#include "types.h"

typedef struct _Link Link;


/**
 * @brief It creates a new link, allocating memory and initializing its members
 * @author María
 *
 * @param id the identification number for the new link
 * @return a new link, initialized
 */
Link* link_create(Id id);

/**
 * @brief It destroys a link, freeing the allocated memory
 * @author María
 *
 * @param link a pointer to the link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link* link);

/**
 * @brief It gets the id of a link
 * @author María
 *
 * @param link a pointer to the space
 * @return the id of link
 */
Id link_get_id(Link* link);

/**
 * @brief It sets the name of a link
 * @author María
 *
 * @param link a pointer to the link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief It gets the name of a link
 * @author María
 *
 * @param link a pointer to the space
 * @return  a string with the name of the link
 */
const char* link_get_name(Link* link);




/**
 * @brief It prints the link information
 * @author María
 *
 * @param space a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link* link);


#endif