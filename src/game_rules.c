/**
 * @brief Implements the game rules for Helios Station (F15)
 *
 * @file game_rules.c
 * @author Your Team
 * @version 1.0
 * @date 28-04-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include <stdlib.h>
#include <time.h>

void game_rules_random_event(Game* game) {
    Player *p = NULL;
    Id p_loc = NO_ID;
    int health = 0;
    int prob = 0;
    Character *alien = NULL;
    Character *dron = NULL;
    Link *door = NULL;
    Id dron_loc = NO_ID;
    Bool has_suit = FALSE, has_oxy = FALSE;

    if (!game) return;

    /* Retrieve the active player */
    p = game_get_active_player(game); 
    if (!p) return;

    p_loc = player_get_location(p);
    health = player_get_health(p);

    /* =========================================================
       DETERMINISTIC RULES (Always occur if conditions are met)
       ========================================================= */

    /* Rule 1: Vacuum in the Airlock (Room 20). Death if missing Suit (3) or Oxygen (4) */
    if (p_loc == 20) {
        has_suit = player_has_object(p, 3);
        has_oxy = player_has_object(p, 4);
        if (has_suit == FALSE || has_oxy == FALSE) {
            player_set_health(p, 0); 
            return; /* End rules execution if player dies */
        }
    }

    /* Rule 2 & 6: Radiation in Reactor (18). Drone (ID 3) protects if in the same room */
    if (p_loc == 18) {
        dron = game_get_character(game, 3);
        if (dron) dron_loc = character_get_location(dron);
        
        /* If the drone is not in the same room, the player suffers radiation damage */
        if (dron_loc != p_loc) {
            player_set_health(p, health - 1);
            health = player_get_health(p); /* Update local health variable */
        }
    }

    /* Rule 3: Healing in the Medbay (Room 15) */
    if (p_loc == 15 && health < 5 && health > 0) {
        player_set_health(p, health + 1);
    }

    /* =========================================================
       RANDOM RULES (Depend on the F15/F16 random generator)
       ========================================================= */
    
    prob = rand() % 100; /* Generates a number from 0 to 99 */

    /* Rule 4: Xenomorph Ambush (10% probability: 0-9) */
    if (prob < 10) {
        alien = game_get_character(game, 1); /* Xenomorph is ID 1 */
        if (alien) {
            character_set_location(alien, p_loc);
            player_set_health(p, player_get_health(p) - 1);
        }
    }
    
    /* Rule 5: Door Short Circuit (10% probability: 10-19) */
    else if (prob >= 10 && prob < 20) {
        /* Temporarily close the link from Airlock to Escape Pod (ID 21) if it exists */
        door = game_get_link(game, 21);
        if (door) {
            link_set_open(door, FALSE);
        }
    }
}