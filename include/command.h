/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Rodrigo and Mario
 * @version 2.0
 * @date 10-04-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 9

typedef enum { CMDS, CMDL } CommandType;

typedef enum { NO_CMD = -1, UNKNOWN, EXIT, MOVE, TAKE, DROP, ATTACK, INSPECT, CHAT } CommandCode;

typedef struct _Command Command;

/**
 * @brief It creates a new command
 * @return a new command, initialized
 */
Command* command_create();

/**
 * @brief It destroys a command
 * @param command a pointer to the command
 * @return OK or ERROR
 */
Status command_destroy(Command* command);

/**
 * @brief It sets the command code
 * @param command a pointer to the command
 * @param code the new command code
 * @return OK or ERROR
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the command code
 * @param command a pointer to the command
 * @return the command code
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It sets the argument of the command (for example, the object to take)
 * @param command a pointer to the command
 * @param arg the argument string
 * @return OK or ERROR
 */
Status command_set_arg(Command* command, char* arg);

/**
 * @brief It gets the argument of the command
 * @param command a pointer to the command
 * @return the argument string
 */
const char* command_get_arg(Command* command);

/**
 * @brief It reads the user input to determine the command and argument
 * @param command a pointer to the command
 * @return OK or ERROR
 */
Status command_get_user_input(Command* command);

#endif