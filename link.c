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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Link
 *
 * This struct stores all the information of a link.
 */
struct _Link
{
    Id id;
    char name[WORD_SIZE];
    Id origin;
    Id destination;
    Direction direction;
    Bool open;
};

Link *link_create(Id id)
{

    Link *newlink = NULL;

    if (id == NO_ID)
    {
        return NULL;
    }

    newlink = (Link *)malloc(sizeof(Link));

    if (!newlink)
    {
        return NULL;
    }

    newlink->id = id;
    newlink->name[0] = '\0';
    newlink->origin = NO_ID;
    newlink->destination = NO_ID;
    newlink->direction = N;
    newlink->open = FALSE;

    return newlink;
}

Status link_destroy(Link *link)
{
    if (link == NULL)
    {
        return ERROR;
    }

    free(link);

    return OK;
}

Status link_set_name(Link *link, char *name)
{
    if (link == NULL || name == NULL)
    {
        return ERROR;
    }

    strncpy(link->name, name, WORD_SIZE - 1);
    return OK;
}

Status link_set_origin(Link *link, Id origin)
{
    if (link == NULL || origin == NO_ID)
    {
        return ERROR;
    }

    link->origin = origin;

    return OK;
}

Status link_set_destination(Link *link, Id destination)
{
    if (link == NULL || destination == NO_ID)
    {
        return ERROR;
    }

    link->destination = destination;

    return OK;
}

Status link_set_direction(Link *link, Direction direction)
{
    if (link == NULL)
    {
        return ERROR;
    }

    link->direction = direction;
    return OK;
}

Status link_set_open(Link *link, Bool open)
{
    if (link == NULL)
    {
        return ERROR;
    }

    link->open = open;
    return OK;
}

Id link_get_id(Link *link)
{
    if (link == NULL)
    {
        return NO_ID;
    }
    return link->id;
}

const char *link_get_name(Link *link)
{
    if (link == NULL)
    {
        return NULL;
    }
    return link->name;
}

Id link_get_origin(Link *link)
{
    if (link == NULL)
    {
        return NO_ID;
    }
    return link->origin;
}

Id link_get_destination(Link *link)
{
    if (link == NULL)
    {
        return NO_ID;
    }
    return link->destination;
}

Direction link_get_direction(Link *link)
{
    if (link == NULL)
    {
        return N;
    }
    return link->direction;
}

Bool link_get_open(Link *link)
{
    if (link == NULL)
    {
        return FALSE;
    }
    return link->open;
}

Status link_print(Link *link)
{
    if (link == NULL)
    {
        return ERROR;
    }

    fprintf(stdout, "--> Link (Id: %ld; Name: %s; Origin: %ld; Dest: %ld; Dir: %d; Open: %d)\n",
            link->id, link->name, link->origin, link->destination, link->direction, link->open);
    return OK;
}
