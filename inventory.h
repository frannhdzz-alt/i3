/**
 * @brief It defines the inventory module interface
 *
 * @file inventory.h
 * @author Mario
 * @version 1.0
 * @date 10-04-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "types.h"
#include "set.h"

typedef struct _Inventory Inventory;

/**
 * @brief It creates a new inventory
 * @author Mario
 * 
 * @param max_objs maximum number of objects the inventory can hold
 * @return a new inventory, initialized
 */
Inventory* inventory_create(int max_objs);

/**
 * @brief It destroys an inventory
 * @author Mario
 * 
 * @param inv a pointer to the inventory to destroy
 * @return OK if everything goes well, ERROR otherwise
 */
Status inventory_destroy(Inventory* inv);

/**
 * @brief It adds an object to the inventory
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @param id the id of the object to add
 * @return OK if added, ERROR otherwise
 */
Status inventory_add_object(Inventory* inv, Id id);

/**
 * @brief It deletes an object from the inventory
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @param id the id of the object to remove
 * @return OK if removed, ERROR otherwise
 */
Status inventory_del_object(Inventory* inv, Id id);

/**
 * @brief It checks if an object is in the inventory
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @param id the id of the object
 * @return TRUE if the object is inside, FALSE otherwise
 */
Bool inventory_has_object(Inventory* inv, Id id);

/**
 * @brief It gets the maximum number of objects allowed
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @return the maximum number of objects, or -1 on error
 */
int inventory_get_max(Inventory* inv);

/**
 * @brief It gets the set of objects in the inventory
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @return a pointer to the set of objects
 */
Set* inventory_get_objects(Inventory* inv);

/**
 * @brief It prints the inventory information
 * @author Mario
 * 
 * @param inv a pointer to the inventory
 * @return OK if everything goes well, ERROR otherwise
 */
Status inventory_print(Inventory* inv);

#endif