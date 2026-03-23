/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 02-03-2026
 * @copyright GNU Public License
 */

#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 50

char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, 
                                   {"n", "Next"}, {"b", "Back"}, {"l", "Left"}, 
                                   {"r", "Right"}, {"t", "Take"}, {"d", "Drop"}, 
                                   {"a", "Attack"}, {"c", "Chat"}};

struct _Command {
  CommandCode code;        /*!< Code of the command */
  char arg[WORD_SIZE];     /*!< Argument of the command */
};

Command* command_create() {
  Command* newCommand = (Command*)calloc(1,sizeof(Command));
  if (newCommand == NULL) return NULL;
  newCommand->code = NO_CMD;
  newCommand->arg[0] = '\0';
  return newCommand;
}

Status command_destroy(Command* command) {
  if (!command) return ERROR;
  free(command);
  return OK;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) return ERROR;
  command->code = code;
  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) return NO_CMD;
  return command->code;
}

Status command_set_arg(Command* command, char* arg) {
  if (!command || !arg) return ERROR;
  strcpy(command->arg, arg);
  return OK;
}

const char* command_get_arg(Command* command) {
  if (!command) return NULL;
  return command->arg;
}

Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "";
  char *token = NULL;
  char *arg = NULL;
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) return ERROR;

  if (fgets(input, CMD_LENGHT, stdin)) {
    
    token = strtok(input, " \r\n");
    if (!token) return command_set_code(command, UNKNOWN);

    arg = strtok(NULL, " \r\n");
    if (arg) strcpy(command->arg, arg);
    else command->arg[0] = '\0';

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }
    return command_set_code(command, cmd);
  } else {
    return command_set_code(command, EXIT);
  }
}