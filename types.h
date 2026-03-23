/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * @brief Common definitions for word size and null identifiers
 */
#define WORD_SIZE 1000
#define NO_ID -1

/**
 * @brief Type definition for identifiers
 */
typedef long Id;

/**
 * @brief Boolean type definition
 */
typedef enum { FALSE, TRUE } Bool;

/**
 * @brief Status type definition for function returns
 */
typedef enum { ERROR, OK } Status;

/**
 * @brief Enumeration of cardinal directions
 */
typedef enum { N, S, E, W } Direction;

#endif