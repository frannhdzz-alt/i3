/**
 * @brief It implements the game rules for Guardians of the Galaxy
 *
 * @file game_rules.c
 * @author Rodrigo, Mario and Francisco
 * @version 8.0
 * @date 28-04-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include "player.h"
#include "character.h"
#include "link.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>

void game_rules_random_event(Game* game) {
    /* Variables at the top for ANSI C compliance */
    Player *p = NULL;
    Id p_loc = NO_ID;
    Id ronan_loc = NO_ID;
    int health = 0;
    int prob = 0;
    int extra_dmg = 0;
    Link *door = NULL;
    Command *last_cmd = NULL;
    Character *ronan = NULL;
    Character *drax = NULL;
    char msg[255]; /* Variable para formatear nuestros mensajes */

    if (!game) return;

    /* Limpiar mensaje del turno anterior */
    game_set_last_message(game, "");

    p = game_get_active_player(game); 
    if (!p) return;

    p_loc = game_get_player_location(game);
    health = player_get_health(p);

    /* =========================================================
       DETERMINISTIC RULES (Game specific logic)
       ========================================================= */

    /* RULE 1: Epic Boss Extra Damage */
    last_cmd = game_get_last_command(game);
    if (last_cmd && command_get_code(last_cmd) == ATTACK) {
        ronan = game_get_character(game, 1);
        drax = game_get_character(game, 4);
        
        if (ronan && character_get_health(ronan) > 0) {
            ronan_loc = game_get_character_location(game, 1);
            if (ronan_loc == p_loc) {
                extra_dmg = 0;
                
                if (player_has_object(p, 7) == TRUE) {
                    extra_dmg += 2;
                }
                if (drax && character_get_following(drax) == player_get_id(p)) {
                    extra_dmg += 2;
                }
                
                if (extra_dmg > 0) {
                    character_set_health(ronan, character_get_health(ronan) - extra_dmg);
                    sprintf(msg, "[COMBAT] Weapons & allies deal %d EXTRA damage to Ronan!", extra_dmg);
                    game_set_last_message(game, msg);
                }
            }
        }
    }

    /* RULE 2: Epic Boss Victory */
    ronan = game_get_character(game, 1);
    if (ronan && character_get_health(ronan) <= 0) {
        game_set_last_message(game, "*** VICTORY! YOU HAVE DEFEATED RONAN THE ACCUSER! ***");
        game_set_finished(game, TRUE);
        return;
    }

    /* RULE 3: Defeat Condition */
    if (health <= 0) {
        game_set_last_message(game, "*** GAME OVER. RONAN HAS DEFEATED YOU. ***");
        game_set_finished(game, TRUE);
        return;
    }

    /* =========================================================
       RANDOM RULES (Surprise events)
       ========================================================= */
    prob = rand() % 100; 

    /* RULE 4: Surprise Attack (10% chance) */
    if (prob < 10) {
        game_set_last_message(game, "[ALERT] Ronan hit you with an energy blast! Lose 1 HP.");
        player_set_health(p, health - 1);
    }
    
    /* RULE 5: Door Malfunction (10% chance) */
    else if (prob >= 10 && prob < 20) {
        door = game_get_link(game, 9); 
        if (door && link_get_open(door) == TRUE) {
            game_set_last_message(game, "[SYSTEM] Power failure. Tower door closed itself.");
            link_set_open(door, FALSE);
        }
    }

    /* RULE 6: Object Displacement (10% chance) */
    else if (prob >= 20 && prob < 30) {
        if (game_get_object_location(game, 19) != 17 && player_has_object(p, 19) == FALSE) {
            game_set_last_message(game, "[SYSTEM] Guards moved the scrap to the vault.");
            game_set_object_location(game, 17, 19);
        }
    }

    /* RULE 7: Unexpected Help (10% chance) */
    else if (prob >= 30 && prob < 40) {
        if (health < 10) {
            game_set_last_message(game, "[HELP] A glowing spore from Groot heals 1 HP.");
            player_set_health(p, health + 1);
        }
    }

    /* RULE 8: Rocket's Distraction (10% chance) */
    else if (prob >= 40 && prob < 50) {
        game_set_last_message(game, "[EVENT] BOOM! Rocket detonated a bomb! Ronan moves.");
        game_set_character_location(game, 13, 1);
    }

    /* RULE 9: Drax's Brute Force (10% chance) */
    else if (prob >= 50 && prob < 60) {
        door = game_get_link(game, 13);
        if (door && link_get_open(door) == FALSE) {
            game_set_last_message(game, "[EVENT] CRASH! Drax smashed open the Hangar door!");
            link_set_open(door, TRUE);
        }
    }
}