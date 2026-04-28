/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Mario
 * @version 2.0
 * @date 13-04-2026
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
#include "link.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100
#define MAX_LINKS 100

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
 * @brief It adds a new player to the game 
 * @author Maria
 *
 * @param game a pointer to the game
 * @param player a pointer to the player to be added
 * @return OK if successful or ERROR if the game is full or pointers are NULL
 */
Status game_add_player(Game *game, Player *player);

/**
 * @brief It gets the active player of the game based on the turn
 * @author Maria
 *
 * @param game a pointer to the game
 * @return a pointer to the active player or NULL in case of error
 */
Player *game_get_active_player(Game *game);

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
 * @brief It adds a link to the game
 * @author Maria
 *
 * @param game pointer to the game
 * @param link pointer to the link to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief It gets a specific link from the game
 * @author Maria
 *
 * @param game a pointer to the game
 * @param id the id of the link
 * @return a pointer to the link, or NULL if it does not exist
 */
Link *game_get_link(Game *game, Id id);

/**
 * @brief It gets the destination space id of a connection
 * @author Maria
 *
 * @param game a pointer to the game
 * @param space the origin space id
 * @param dir the direction of the connection
 * @return the destination space id, or NO_ID if there is no connection
 */
Id game_get_connection(Game *game, Id space, Direction dir);

/**
 * @brief It checks if a connection is open
 * @author Maria
 *
 * @param game a pointer to the game
 * @param space the origin space id
 * @param dir the direction of the connection
 * @return TRUE if the connection is open, FALSE otherwise
 */
Bool game_connection_is_open(Game *game, Id space, Direction dir);

/**
 * @brief It gets the last command executed in the game
 * @author Mario
 *
 * @param game a pointer to the game
 * @return a pointer to the last command
 */
Command *game_get_last_command(Game *game);

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
 * @brief It sets the discovered status of a space
 * @author Francisco
 *
 * @param game a pointer to the game
 * @param space_id the id of the space
 * @param discovered the new discovered status (TRUE or FALSE)
 * @return OK if successful or ERROR in case of error
 */
Status game_set_space_discovered(Game* game, Id space_id, Bool discovered);

/**
 * @brief It checks if a space has been discovered
 * @author Francisco
 *
 * @param game a pointer to the game
 * @param space_id the id of the space
 * @return TRUE if the space has been discovered, FALSE otherwise
 */
Bool game_get_space_discovered(Game* game, Id space_id);


/**
 * @brief It gets the id of the destination space through a link
 * @author Francisco
 *
 * @param game a pointer to the game
 * @param space_id the id of the origin space
 * @param dir the direction of the movement
 * @return the id of the destination space if the link is open, or NO_ID otherwise
 */
Id game_get_connection(Game *game, Id space_id, Direction dir);

/**
 * @brief It prints the game information
 * @author Mario
 *
 * @param game a pointer to the game
 */
void game_print(Game *game);

/**
 * @brief It updates the game turn to the next player (0 or 1)
 * @author Maria
 *
 * @param game a pointer to the game
 * @return OK if successful or ERROR in case of error
 */
Status game_next_turn(Game *game);

/**
 * @brief It gets a character by its name
 * @author Mario
 *
 * @param game a pointer to the game
 * @return a pointer to the character with the given name, or NULL if it does not exist
 */
Character* game_get_character_by_name(Game *game, const char *name);

/**
 * @brief It recruits a character to follow the active player
 * @author Mario
 *
 * @param game a pointer to the game
 * @return OK if successful or ERROR in case of error
 */
Status game_recruit_character(Game *game, Id player_id, const char *char_name);


#endif