/**
 * @brief It implements the game rules for Guardians of the Galaxy
 *
 * @file game_rules.c
 * @author Rodrigo, Mario and Francisco
 * @version 7.0
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
    /* TODAS LAS VARIABLES ARRIBA DEL TODO (Obligatorio en ANSI C) */
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

    if (!game) return;

    p = game_get_active_player(game); 
    if (!p) return;

    p_loc = game_get_player_location(game);
    health = player_get_health(p);

    /* =========================================================
       DETERMINISTIC RULES (Game specific logic)
       ========================================================= */

    /* RULE 1: Epic Boss Extra Damage 
       If the last command was ATTACK, check if we are hitting Ronan with bonuses. */
    last_cmd = game_get_last_command(game);
    if (last_cmd && command_get_code(last_cmd) == ATTACK) {
        ronan = game_get_character(game, 1);
        drax = game_get_character(game, 4);
        
        if (ronan && character_get_health(ronan) > 0) {
            /* Fix: Check if Ronan is in the same room as the player (p_loc) */
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
                    fprintf(stdout, "\n[COMBAT RULE] Your weapons/allies deal %d EXTRA damage to Ronan!\n", extra_dmg);
                }
            }
        }
    }

    /* RULE 2: Epic Boss Victory
       If Ronan reaches 0 HP, you win the game. */
    ronan = game_get_character(game, 1);
    if (ronan && character_get_health(ronan) <= 0) {
        fprintf(stdout, "\n======================================================\n");
        fprintf(stdout, " BOOOOM! YOU HAVE DEFEATED RONAN THE ACCUSER.\n");
        fprintf(stdout, " THE GALAXY IS SAFE. YOU ARE A TRUE GUARDIAN.\n");
        fprintf(stdout, " \n *** VICTORY! YOU HAVE WON THE GAME! ***\n");
        fprintf(stdout, "======================================================\n");
        game_set_finished(game, TRUE);
        return;
    }

    /* RULE 3: Defeat Condition
       If your health drops to 0 or less, you die and the game ends. */
    if (health <= 0) {
        fprintf(stdout, "\n*** GAME OVER. RONAN HAS DEFEATED YOU. ***\n");
        game_set_finished(game, TRUE);
        return;
    }

    /* =========================================================
       RANDOM RULES (Surprise events)
       ========================================================= */
    prob = rand() % 100; 

    /* RULE 4: Surprise Attack (10% chance - 0 to 9) */
    if (prob < 10) {
        fprintf(stdout, "\n[ALERT] Ronan hit you with an energy blast! You lose 1 HP.\n");
        player_set_health(p, health - 1);
    }
    
    /* RULE 5: Door Malfunction (10% chance - 10 to 19) */
    else if (prob >= 10 && prob < 20) {
        door = game_get_link(game, 9); 
        if (door && link_get_open(door) == TRUE) {
            fprintf(stdout, "\n[SYSTEM] Power failure. The Tower door has closed itself.\n");
            link_set_open(door, FALSE);
        }
    }

    /* RULE 6: Object Displacement (10% chance - 20 to 29) */
    else if (prob >= 20 && prob < 30) {
        if (game_get_object_location(game, 19) != 17 && player_has_object(p, 19) == FALSE) {
            fprintf(stdout, "\n[SYSTEM] The guards have moved the scrap to the vault.\n");
            game_set_object_location(game, 17, 19);
        }
    }

    /* RULE 7: Unexpected Help (10% chance - 30 to 39) */
    else if (prob >= 30 && prob < 40) {
        if (health < 10) {
            fprintf(stdout, "\n[HELP] A glowing spore from Groot heals 1 HP.\n");
            player_set_health(p, health + 1);
        }
    }

    /* RULE 8: Rocket's Distraction (10% chance - 40 to 49) */
    else if (prob >= 40 && prob < 50) {
        fprintf(stdout, "\n[EVENT] BOOM! Rocket detonated a bomb in the Canteen! Ronan investigates.\n");
        game_set_character_location(game, 13, 1);
    }

    /* RULE 9: Drax's Brute Force (10% chance - 50 to 59) */
    else if (prob >= 50 && prob < 60) {
        door = game_get_link(game, 13);
        if (door && link_get_open(door) == FALSE) {
            fprintf(stdout, "\n[EVENT] CRASH! Drax got impatient and smashed open the Hangar door!\n");
            link_set_open(door, TRUE);
        }
    }
}