/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Mario
 * @version 3.0
 * @date 13-04-2026
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "inventory.h"

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
 * @brief It adds an object to the player's backpack
 * @author Mario
 *
 * @param player A pointer to the player
 * @param id The id of the object to add
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_add_object(Player* player, Id id);

/**
 * @brief It removes an object from the player's backpack
 * @author Mario
 *
 * @param player A pointer to the player
 * @param id The id of the object to remove
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_del_object(Player* player, Id id);

/**
 * @brief It checks if the player has an object in the backpack
 * @author Mario
 *
 * @param player A pointer to the player
 * @param id The id of the object
 * @return TRUE if the object is in the backpack, FALSE otherwise
 */
Bool player_has_object(Player* player, Id id);

/**
 * @brief It gets the player's inventory
 * @author Mario
 *
 * @param player A pointer to the player
 * @return A pointer to the inventory, or NULL if error
 */
Inventory* player_get_inventory(Player* player);

/**
 * @brief It sets the health of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param health The health value to set
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_health(Player* player, int health);

/**
 * @brief It gets the health of a player
  * @author Mario
 *
 * @param player A pointer to the player
 * @return The health value, or -1 if error
 */
int player_get_health(Player* player);

/**
 * @brief It sets the graphic description of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @param gdesc A string with the graphic description to store
 * @return OK if everything goes well, ERROR otherwise
 */
Status player_set_gdesc(Player* player, char* gdesc);

/**
 * @brief It gets the graphic description of a player
 * @author Mario
 *
 * @param player A pointer to the player
 * @return A string with the graphic description of the player, or NULL if error
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