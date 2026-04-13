/**
 * @brief It defines the game update interface through user actions
 *
 * @file game_actions.h
 * @author Rodrigo and Mario
 * @version 3.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
 * @brief It updates the game state depending on the received command
 * @author Rodrigo and Mario
 *
 * @param game a pointer to the game
 * @param cmd a pointer to the command received
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_actions_update(Game *game, Command *cmd);

#endif