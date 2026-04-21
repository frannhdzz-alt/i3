/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author Mario
 * @version 1.0
 * @date 22-02-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

typedef struct _Character Character;

/**
 * @brief It creates a new character
 * @author Mario
 *
 * @param id The identification number for the new character
 * @return A new character, initialized, or NULL if there was an error
 */
Character* character_create(Id id);

/**
 * @brief It destroys a character
 * @author Mario
 *
 * @param character A pointer to the character to be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_destroy(Character* character);

/**
 * @brief It gets the id of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @return The character id, or NO_ID if there is an error
 */
Id character_get_id(Character* character);

/**
 * @brief It sets the name of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @param name A string with the name to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_set_name(Character* character, char* name);

/**
 * @brief It gets the name of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @return A string with the name of the character, or NULL if error
 */
const char* character_get_name(Character* character);

/**
 * @brief It sets the graphic description of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @param gdesc A string with the graphic description (6 chars)
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_set_gdesc(Character* character, char* gdesc);

/**
 * @brief It gets the graphic description of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @return A string with the graphic description, or NULL if error
 */
const char* character_get_gdesc(Character* character);

/**
 * @brief It sets the health of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @param health The health points to set
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_set_health(Character* character, int health);

/**
 * @brief It gets the health of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @return The character's health points, or -1 if error
 */
int character_get_health(Character* character);

/**
 * @brief It sets if the character is friendly or not
 * @author Mario
 *
 * @param character A pointer to the character
 * @param friendly TRUE if friendly, FALSE otherwise
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_set_friendly(Character* character, Bool friendly);

/**
 * @brief It gets if the character is friendly
 * @author Mario
 *
 * @param character A pointer to the character
 * @return TRUE if friendly, FALSE otherwise
 */
Bool character_get_friendly(Character* character);

/**
 * @brief It sets the message of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @param message A string with the message to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_set_message(Character* character, char* message);

/**
 * @brief It gets the message of a character
 * @author Mario
 *
 * @param character A pointer to the character
 * @return A string with the character's message, or NULL if error
 */
const char* character_get_message(Character* character);

/**
 * @brief It prints the character information
 * @author Mario
 *
 * @param character A pointer to the character
 * @return OK if everything goes well, ERROR otherwise
 */
Status character_print(Character* character);

#endif