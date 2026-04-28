/**
 * @brief It implements the game rules for Helios Station (F15)
 *
 * @file game_rules.c
 * @author Rodrigo, Mario y Francisco
 * @version 3.0
 * @date 28-04-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include "player.h"
#include "character.h"
#include "link.h"
#include <stdlib.h>

/**
 * @brief Executes the game rules at the end of each turn
 */
void game_rules_random_event(Game* game) {
    Player *p = NULL;
    Id p_loc = NO_ID;
    int health = 0;
    int prob = 0;
    Character *alien = NULL;
    Link *door = NULL;

    if (!game) return;

    /* 1. Get the active player using game.h: line 104 */
    p = game_get_active_player(game); 
    if (!p) return;

    /* 2. Get player location and health */
    p_loc = game_get_player_location(game); /* game.h: line 126 */
    health = player_get_health(p);

    /* =========================================================
       DETERMINISTIC RULES
       ========================================================= */

    /* Rule 1: Vacuum in the Airlock (Room 20)
       Check if objects 3 (Suit) and 4 (Oxygen) are with the player.
       We check if their location matches the player location */
    if (p_loc == 20) {
        if (game_get_object_location(game, 3) != p_loc || 
            game_get_object_location(game, 4) != p_loc) {
            /* If the player doesn't have the equipment, health goes to 0 */
            player_set_health(p, 0);
            game_set_finished(game, TRUE);
            return;
        }
    }

    /* Rule 2: Radiation in Reactor (Room 18) */
    if (p_loc == 18 && health > 0) {
        player_set_health(p, health - 1);
        health = player_get_health(p); 
    }

    /* Rule 3: Healing in the Medbay (Room 15) */
    if (p_loc == 15 && health < 5 && health > 0) {
        player_set_health(p, health + 1);
    }

    /* =========================================================
       RANDOM RULES
       ========================================================= */
    
    prob = rand() % 100; 

    /* Rule 4: Xenomorph Ambush (10% probability) */
    if (prob < 10) {
        /* game_get_character(game, id) as defined in your game.h: line 118 */
        alien = game_get_character(game, 1); 
        if (alien) {
            /* Move alien to player location: game.h line 172 */
            game_set_character_location(game, p_loc, 1);
            player_set_health(p, health - 1);
        }
    }
    
    /* Rule 5: Door Short Circuit (10% probability) */
    else if (prob >= 10 && prob < 20) {
        /* game_get_link(game, id) as defined in your game.h: line 181 */
        door = game_get_link(game, 21); 
        if (door) {
            link_set_open(door, FALSE);
        }
    }
}