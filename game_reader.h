/**
 * @brief It defines the game reader module interface
 *
 * @file game_reader.h
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"
#include "types.h"

/**
 * @brief It creates a game reading it from a file
 * @param game A pointer to the game pointer to be initialized
 * @param filename The name of the file to read
 * @return OK if everything goes well, ERROR otherwise
 */
Status game_create_from_file(Game **game, char *filename);

#endif