/**
 * @brief It implements the link module
 *
 * @file link.c
 * @author María Gómez
 * @version 1.0
 * @date 23-03-2026
 * @copyright GNU Public License
 */

#include "link.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Link {
    Id id;
    char name[MAX_NAME];
    Id origin;
    Id destination;
    Direction direction;
    Bool open;
};



