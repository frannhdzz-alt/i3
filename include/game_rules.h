/**
 * @brief Defines the game rules module for Helios Station
 *
 * @file game_rules.h
 * @author Rodrigo
 * @version 1.0
 * @date 28-04-2026
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"

/**
 * @brief Executes the random and passive events of the ship at the end of a turn.
 * @param game Pointer to the current game structure.
 */
void game_rules_random_event(Game* game);

#endif