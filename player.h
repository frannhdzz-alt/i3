/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Mario
 * @version 2.0
 * @date 24-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new player
 * @author Mario
 *
 * @param id The identification number for the new player
 * @return A new player, initialized, or NULL if error
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player
 * @author Mario
 *
 * @param player A pointer to the player to be destroyed
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return The player id, or NO_ID if error
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param name A string with the name to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return A string with the name of the player, or NULL if error
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the location of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param id The id of the space where the player is located
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_location(Player* player, Id id);

/**
 * @brief It gets the location of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return The id of the space where the player is
 */
Id player_get_location(Player* player);

/**
 * @brief It sets the object carried by the player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param id The id of the object carried
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_object(Player* player, Id id);

/**
 * @brief It gets the object carried by the player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return The id of the object carried
 */
Id player_get_object(Player* player);

/**
 * @brief It sets the health of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param health The health points to set
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_health(Player* player, int health);

/**
 * @brief It gets the health of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return The player's health points, or -1 if error
 */
int player_get_health(Player* player);

/**
 * @brief It sets the graphic description of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param gdesc A string with the graphic description
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_gdesc(Player* player, char* gdesc);

/**
 * @brief It gets the graphic description of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return A string with the graphic description, or NULL if error
 */
const char* player_get_gdesc(Player* player);

/**
 * @brief It prints the player information
 * @author Mario
 *
 * @param player A pointer to the player
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_print(Player* player);

#endif