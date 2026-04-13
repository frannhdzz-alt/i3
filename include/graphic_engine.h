/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 05-04-2026
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates the graphic engine
 * @author Rodrigo and Mario
 *
 * @return a pointer to the graphic engine
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys the graphic engine
 * @author Rodrigo and Mario
 *
 * @param ge a pointer to the graphic engine
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It paints the game state on the screen
 * @author Rodrigo and Mario
 *
 * @param ge a pointer to the graphic engine
 * @param game a pointer to the game
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif