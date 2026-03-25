/**
 * @brief It implements the inventory module
 *
 * @file link.c
 * @author Mario
 * @version 1.0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>

#include "inventory.h"

struct _Inventory {
    Set* objs;
    int max_objs;
};

Inventory* inventory_create(int max_objs) {
    Inventory* inv = NULL;

    if (max_objs <= 0)
        return NULL;

    inv = (Inventory*) malloc(sizeof(Inventory));
    if (!inv)
        return NULL;

    inv->objs = set_create();
    if (!inv->objs) {
        free(inv);
        return NULL;
    }

    inv->max_objs = max_objs;

    return inv;
}

Status inventory_destroy(Inventory* inv) {
    if (!inv)
        return ERROR;

    set_destroy(inv->objs);
    free(inv);

    return OK;
}

Status inventory_add_object(Inventory* inv, Id id) {
    if (!inv || id == NO_ID)
        return ERROR;

    /* Check inventory capacity */
    if (set_get_n_ids(inv->objs) >= inv->max_objs)
        return ERROR;

    return set_add(inv->objs, id);
}

Status inventory_del_object(Inventory* inv, Id id) {
    if (!inv || id == NO_ID)
        return ERROR;

    return set_del(inv->objs, id);
}

Bool inventory_has_object(Inventory* inv, Id id) {
    if (!inv || id == NO_ID)
        return FALSE;

    return set_find(inv->objs, id);
}

int inventory_get_max(Inventory* inv) {
    if (!inv)
        return -1;

    return inv->max_objs;
}

Set* inventory_get_objects(Inventory* inv) {
    if (!inv)
        return NULL;

    return inv->objs;
}

Status inventory_print(Inventory* inv) {
    if (!inv)
        return ERROR;

    printf("Inventory:\n");
    printf("  Max objects: %d\n", inv->max_objs);
    printf("  Objects:\n");
    set_print(inv->objs);

    return OK;
}