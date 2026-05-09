/**
 * @file inventory_test.c
 * @author Rodrigo
 * @date 01-05-2026
 * @brief Unit tests for the Inventory module
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#define PRINT_TEST_RESULT(pass) do { \
    if (pass) printf("[OK] %s:%d\n", __FILE__, __LINE__); \
    else printf("[FAIL] %s:%d\n", __FILE__, __LINE__); \
} while(0)

void test1_inventory_create() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inv != NULL); 
    inventory_destroy(inv); 
}

void test2_inventory_create() { 
    Inventory *inv = inventory_create(0); 
    PRINT_TEST_RESULT(inv == NULL); 
}

void test1_inventory_destroy() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_destroy(inv) == OK); 
}

void test2_inventory_destroy() { 
    Inventory *inv = NULL; 
    PRINT_TEST_RESULT(inventory_destroy(inv) == ERROR); 
}

void test1_inventory_add_object() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_add_object(inv, 10) == OK); 
    inventory_destroy(inv); 
}

void test2_inventory_add_object() { 
    Inventory *inv = inventory_create(1); 
    inventory_add_object(inv, 10); 
    PRINT_TEST_RESULT(inventory_add_object(inv, 11) == ERROR); 
    inventory_destroy(inv); 
}

void test1_inventory_del_object() { 
    Inventory *inv = inventory_create(5); 
    inventory_add_object(inv, 10); 
    PRINT_TEST_RESULT(inventory_del_object(inv, 10) == OK); 
    inventory_destroy(inv); 
}

void test2_inventory_del_object() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_del_object(inv, 10) == ERROR); 
    inventory_destroy(inv); 
}

void test1_inventory_has_object() { 
    Inventory *inv = inventory_create(5); 
    inventory_add_object(inv, 10); 
    PRINT_TEST_RESULT(inventory_has_object(inv, 10) == TRUE); 
    inventory_destroy(inv); 
}

void test2_inventory_has_object() { 
    PRINT_TEST_RESULT(inventory_has_object(NULL, 10) == FALSE); 
}

void test1_inventory_get_max() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_get_max(inv) == 5); 
    inventory_destroy(inv); 
}

void test2_inventory_get_max() { 
    PRINT_TEST_RESULT(inventory_get_max(NULL) == -1); 
}

void test1_inventory_get_objects() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_get_objects(inv) != NULL); 
    inventory_destroy(inv); 
}

void test2_inventory_get_objects() { 
    PRINT_TEST_RESULT(inventory_get_objects(NULL) == NULL); 
}

void test1_inventory_print() { 
    Inventory *inv = inventory_create(5); 
    PRINT_TEST_RESULT(inventory_print(inv) == OK); 
    inventory_destroy(inv); 
}

void test2_inventory_print() { 
    PRINT_TEST_RESULT(inventory_print(NULL) == ERROR); 
}

int main() {
    printf("Running INVENTORY tests...\n");
    test1_inventory_create(); test2_inventory_create();
    test1_inventory_destroy(); test2_inventory_destroy();
    test1_inventory_add_object(); test2_inventory_add_object();
    test1_inventory_del_object(); test2_inventory_del_object();
    test1_inventory_has_object(); test2_inventory_has_object();
    test1_inventory_get_max(); test2_inventory_get_max();
    test1_inventory_get_objects(); test2_inventory_get_objects();
    test1_inventory_print(); test2_inventory_print();
    return 0;
}