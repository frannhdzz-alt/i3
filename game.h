/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Mario
 * @version 2.0
 * @date 26-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "player.h" 
#include "object.h"
#include "character.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100


typedef struct _Game Game;

/**
 * @brief It creates a new game, initializing its members
 * @author Mario
 *
 * @param game a pointer to the game pointer to be initialized
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create(Game **game);

/**
 * @brief It destroys a game, freeing the allocated memory for its members
 * @author Mario
 *
 * @param game a pointer to the game to be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief It adds a space to the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param space a pointer to the space to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It adds an object to the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param object a pointer to the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief It adds a character to the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param character a pointer to the character to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It gets the id of the space located at a specific position in the spaces array
 * @author Mario
 *
 * @param game a pointer to the game
 * @param position the index in the spaces array
 * @return the id of the space, or NO_ID if the position is invalid
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief It gets the space pointer associated with a specific id
 * @author Mario
 *
 * @param game a pointer to the game
 * @param id the identification number of the space
 * @return a pointer to the space, or NULL if it does not exist
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the player of the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @return a pointer to the player
 */
Player *game_get_player(Game *game);

/**
 * @brief It sets the player of the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param player a pointer to the player to be set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player(Game *game, Player *player);

/**
 * @brief It gets a specific object from the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param id the id of the object
 * @return a pointer to the object, or NULL if it does not exist
 */
Object *game_get_object(Game *game, Id id);

/**
 * @brief It gets a specific character from the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param id the id of the character
 * @return a pointer to the character, or NULL if it does not exist
 */
Character *game_get_character(Game *game, Id id);

/**
 * @brief It gets the current location id of the player
 * @author Mario
 *
 * @param game a pointer to the game
 * @return the id of the space where the player is located
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the current location id of the player
 * @author Mario
 *
 * @param game a pointer to the game
 * @param id the id of the space where the player will be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It gets the current location id of a specific object
 * @author Mario
 *
 * @param game a pointer to the game
 * @param object_id the id of the object
 * @return the id of the space where the object is located
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief It sets the current location id of a specific object
 * @author Mario
 *
 * @param game a pointer to the game
 * @param space_id the id of the space where the object will be placed
 * @param object_id the id of the object to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/**
 * @brief It gets the current location id of a specific character
 * @author Mario
 *
 * @param game a pointer to the game
 * @param char_id the id of the character
 * @return the id of the space where the character is located
 */
Id game_get_character_location(Game *game, Id char_id);

/**
 * @brief It sets the current location id of a specific character
 * @author Mario
 *
 * @param game a pointer to the game
 * @param space_id the id of the space where the character will be placed
 * @param char_id the id of the character to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_character_location(Game *game, Id space_id, Id char_id);

/**
 * @brief It gets the last command executed in the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @return a pointer to the last command
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It sets the last command executed in the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param command a pointer to the command to be set as the last one
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It checks whether the game is finished or not
 * @author Mario
 *
 * @param game a pointer to the game
 * @return TRUE if the game is finished, FALSE otherwise
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets the finished state of the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @param finished the new state (TRUE or FALSE)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Cambia el estado de descubrimiento de un espacio
 */
Status game_set_space_discovered(Game* game, Id space_id, Bool discovered);

/**
 * @brief Comprueba si un espacio ha sido descubierto
 */
Bool game_get_space_discovered(Game* game, Id space_id);

/**
 * @brief It prints the game information
 * @author Mario
 *
 * @param game a pointer to the game
 */
void game_print(Game *game);

#endif