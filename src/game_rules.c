/**
 * @brief It implements the game rules for Guardians of the Galaxy
 *
 * @file game_rules.c
 * @author Rodrigo
 * @version 1.0
 * @date 01-05-2026
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
  
    static Id last_turn_player_id = 1; 
    Player *p = NULL, *attacker = NULL;
    Id ronan_loc = NO_ID, attacker_id = NO_ID, random_dest = NO_ID;
    int health = 0, prob = 0, extra_dmg = 0;
    int has_ally = 0, has_weap = 0; 
    Link *door = NULL;
    Command *last_cmd = NULL;
    Character *ronan = NULL, *rocket = NULL, *drax = NULL;
    char msg[255];

    Id valid_spaces[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 25, 26, 27};
    int n_valid_spaces = 15;

    if (!game) return;

    game_set_last_message(game, ""); 

    p = game_get_active_player(game); 
    if (!p) return;

    health = player_get_health(p);

    /* =========================================================
       DETERMINISTIC RULES 
       ========================================================= */

    last_cmd = game_get_last_command(game);
    if (last_cmd && command_get_code(last_cmd) == ATTACK) {
        ronan = game_get_character(game, 1);
        if (ronan && character_get_health(ronan) > 0) {
            ronan_loc = game_get_character_location(game, 1);
            
            attacker = game_get_player_by_id(game, last_turn_player_id);
            if (!attacker) attacker = p; 

            if (attacker && player_get_location(attacker) == ronan_loc) {
                attacker_id = player_get_id(attacker);
                extra_dmg = 0;
                has_ally = 0;
                has_weap = 0;
                
                if (attacker_id == 1) { /* Star-Lord */
                    rocket = game_get_character(game, 2); 
                    if (rocket && character_get_following(rocket) == attacker_id) { extra_dmg += 2; has_ally = 1; }
                    if (player_has_object(attacker, 7) == TRUE) { extra_dmg += 3; has_weap = 1; }
                    
                    if (extra_dmg > 0) {
                        if (has_ally && has_weap) sprintf(msg, "[STAR-LORD] Rocket & Blaster boost: +%d dmg!", extra_dmg);
                        else if (has_weap) sprintf(msg, "[STAR-LORD] Blaster shot: +%d dmg!", extra_dmg);
                        else sprintf(msg, "[STAR-LORD] Rocket cover fire: +%d dmg!", extra_dmg);
                        game_set_last_message(game, msg);
                    }
                }
                else if (attacker_id == 2) { /* Gamora */
                    drax = game_get_character(game, 4); 
                    if (drax && character_get_following(drax) == attacker_id) { extra_dmg += 2; has_ally = 1; }
                    if (player_has_object(attacker, 3) == TRUE) { extra_dmg += 3; has_weap = 1; }
                    
                    if (extra_dmg > 0) {
                        if (has_ally && has_weap) sprintf(msg, "[GAMORA] Drax & Knife combo: +%d dmg!", extra_dmg);
                        else if (has_weap) sprintf(msg, "[GAMORA] Knife slash: +%d dmg!", extra_dmg);
                        else sprintf(msg, "[GAMORA] Drax brute force: +%d dmg!", extra_dmg);
                        game_set_last_message(game, msg);
                    }
                }
                
                if (character_get_health(ronan) <= extra_dmg + 1) {
                    game_set_last_message(game, "*** VICTORY! RONAN HAS BEEN DEFEATED! ***");
                    game_set_finished(game, TRUE);
                   
                    last_turn_player_id = player_get_id(p);
                    return;
                } else {
                    character_set_health(ronan, character_get_health(ronan) - extra_dmg);
                }
            }
        }
    }

    ronan = game_get_character(game, 1);
    if (ronan && character_get_health(ronan) <= 0) {
        game_set_last_message(game, "*** VICTORY! RONAN HAS BEEN DEFEATED! ***");
        game_set_finished(game, TRUE);
        last_turn_player_id = player_get_id(p);
        return;
    }
    if (health <= 0) {
        game_set_last_message(game, "*** GAME OVER. YOU DIED IN KYLN PRISON. ***");
        game_set_finished(game, TRUE);
        last_turn_player_id = player_get_id(p);
        return;
    }

    /* =========================================================
       RANDOM RULES 
       ========================================================= */
    prob = rand() % 100; 

    if (prob < 10) {
        game_set_last_message(game, "[ALERT] Ronan blast! You lose 1 HP.");
        player_set_health(p, health - 1);
    }
    else if (prob >= 10 && prob < 20) {
        door = game_get_link(game, 9); 
        if (door) {
            game_set_last_message(game, "[SYSTEM] Security breach. Tower door state changed.");
            link_set_open(door, !link_get_open(door));
        }
    }
    else if (prob >= 40 && prob < 50) {
        random_dest = valid_spaces[rand() % n_valid_spaces];
        game_set_last_message(game, "[EVENT] Rocket detonated a bomb! Ronan warped.");
        game_set_character_location(game, random_dest, 1);
    }
    else if (prob >= 50 && prob < 60) {
        door = game_get_link(game, 13);
        if (door && link_get_open(door) == FALSE) {
            game_set_last_message(game, "[EVENT] Drax smashed open the Hangar door!");
            link_set_open(door, TRUE);
        }
    }

    last_turn_player_id = player_get_id(p);
}