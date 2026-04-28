/**
 * @brief It implements the main game loop
 *
 * @file game_loop.c
 * @author Rodrigo, Mario y Francisco
 * @version 4.1
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_reader.h"
#include "game_rules.h"


int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);


extern char *cmd_to_str[N_CMD][N_CMDT];

int main(int argc, char *argv[]) {
  Game *game = NULL;
  Graphic_engine *gengine = NULL;
  Command *last_cmd;
  
  FILE *f_log = NULL; 
  Status action_status = ERROR;
  CommandCode cmd_code;
  const char *cmd_arg;

  /* F16: Variables for Deterministic Mode and argument parsing */
  /* We declare them here at the top to comply with ANSI C standards */
  int i;
  int seed = -1;
  int result;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>] [-d <seed>]\n", argv[0]);
    return 1;
  }

  /* Parse command line arguments for Log and Seed */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0 && (i + 1) < argc) {
      f_log = fopen(argv[i + 1], "w");
      if (f_log == NULL) {
        fprintf(stderr, "Warning: Could not open log file '%s'\n", argv[i + 1]);
      }
    } 
    else if (strcmp(argv[i], "-d") == 0 && (i + 1) < argc) {
      seed = atoi(argv[i + 1]);
    }
  }

  /* F16: Initialize random number generator with explicit casting to unsigned int */
  if (seed != -1) {
    srand((unsigned int)seed); 
  } else {
    srand((unsigned int)time(NULL)); 
  }

  result = game_loop_init(&game, &gengine, argv[1]);

  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    if (f_log) fclose(f_log);
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    if (f_log) fclose(f_log);
    return 1;
  }

  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    
    action_status = game_actions_update(game, last_cmd);

    if (action_status == OK && command_get_code(last_cmd) != UNKNOWN && command_get_code(last_cmd) != NO_CMD) {
      game_next_turn(game);

      /* F15: Evaluate game rules */
      game_rules_random_event(game);
    }
    
    if (f_log != NULL) {
      cmd_code = command_get_code(last_cmd);
      cmd_arg = command_get_arg(last_cmd);
      
      if (cmd_arg != NULL && cmd_arg[0] != '\0') {
        fprintf(f_log, "%s %s: %s\n", cmd_to_str[cmd_code - NO_CMD][CMDL], cmd_arg, (action_status == OK) ? "OK" : "ERROR");
      } else {
        fprintf(f_log, "%s: %s\n", cmd_to_str[cmd_code - NO_CMD][CMDL], (action_status == OK) ? "OK" : "ERROR");
      }
    }
  }

  if (game_get_finished(game) == TRUE) {
      graphic_engine_paint_game(gengine, game);
      printf("\n\nGAME OVER!\n");
  }

  game_loop_cleanup(game, gengine);
  
  if (f_log != NULL) {
    fclose(f_log);
  }

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  if (game_create_from_file(game, file_name) == ERROR) {
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    game_destroy(*game);
    return 2;
  }

  return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  game_destroy(game);
  graphic_engine_destroy(gengine);
}