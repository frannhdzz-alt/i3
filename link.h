/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author María Gómez
 * @version 1.0
 * @date 10-04-2026
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
Link *link_create(Id id);

/**
 * @brief It destroys a link, freeing the allocated memory
 * @author María
 *
 * @param link a pointer to the link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link *link);

/**
 * @brief It sets the name of a link
 * @author María
 *
 * @param link a pointer to the link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link *link, char *name);

/**
 * @brief It sets the origin space of a link
 * @author María
 *
 * @param link a pointer to the link
 * @param origin id of the space where the link starts
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_origin(Link *link, Id origin);

/**
 * @brief It sets the destination space of a link
 * @author María
 *
 * @param link a pointer to the link
 * @param destination id of the space where the link ends
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_destination(Link *link, Id destination);

/**
 * @brief It sets the direction of a link
 * @author María
 *
 * @param link a pointer to the link
 * @param direction direction of the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_direction(Link *link, Direction direction);

/**
 * @brief It changes the status of a link to open or closed
 * @author María
 *
 * @param link a pointer to the link
 * @param open TRUE if link is open, FALSE if link is closed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_open(Link *link, Bool open);

/**
 * @brief It gets the id of a link
 * @author María
 *
 * @param link a pointer to the space
 * @return the id of link or NO_ID in case of error
 */
Id link_get_id(Link *link);

/**
 * @brief Gets the name of a link
 * @author María
 *
 * @param link Pointer to the link
 * @return A pointer to the string with the name or NULL in case of error
 */
const char *link_get_name(Link *link);

/**
 * @brief Gets the origin space of a link
 * @author María
 *
 * @param link Pointer to the link
 * @return The Id of the origin space or NO_ID in case of error
 */
Id link_get_origin(Link *link);

/**
 * @brief Gets the destination space of a link
 * @author María
 *
 * @param link Pointer to the link
 * @return The Id of the destination space or NO_ID in case of error
 */
Id link_get_destination(Link *link);

/**
 * @brief Gets the direction of a link
 * @author María
 *
 * @param link Pointer to the link
 * @return The direction of the link (Direction) or U (Unknown) in case of error
 */
Direction link_get_direction(Link *link);

/**
 * @brief Checks if a link is open or closed
 * @author María
 *
 * @param link Pointer to the link
 * @return TRUE if it is open, FALSE if it is closed or if there is an error
 */
Bool link_get_open(Link *link);

/**
 * @brief It prints the link information
 * @author María
 *
 * @param space a pointer to the link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link *link);

#endif