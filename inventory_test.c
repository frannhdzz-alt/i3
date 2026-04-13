/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @author Rodrigo
 * @version 2.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_inventory_create() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inv != NULL, "test1_inventory_create");
  inventory_destroy(inv);
}

void test2_inventory_create() {
  Inventory *inv = inventory_create(0);
  PRINT_TEST_RESULT(inv == NULL, "test2_inventory_create");
}

void test1_inventory_add_object() {
  Inventory *inv = inventory_create(2);
  PRINT_TEST_RESULT(inventory_add_object(inv, 10) == OK, "test1_inventory_add_object");
  inventory_destroy(inv);
}

void test2_inventory_add_object() {
  Inventory *inv = inventory_create(1);
  inventory_add_object(inv, 10);
  PRINT_TEST_RESULT(inventory_add_object(inv, 11) == ERROR, "test2_inventory_add_object");
  inventory_destroy(inv);
}

void test1_inventory_del_object() {
  Inventory *inv = inventory_create(2);
  inventory_add_object(inv, 10);
  PRINT_TEST_RESULT(inventory_del_object(inv, 10) == OK, "test1_inventory_del_object");
  inventory_destroy(inv);
}

void test2_inventory_del_object() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_del_object(inv, 10) == ERROR, "test2_inventory_del_object");
}

void test1_inventory_has_object() {
  Inventory *inv = inventory_create(2);
  inventory_add_object(inv, 10);
  PRINT_TEST_RESULT(inventory_has_object(inv, 10) == TRUE, "test1_inventory_has_object");
  inventory_destroy(inv);
}

void test2_inventory_has_object() {
  Inventory *inv = inventory_create(2);
  PRINT_TEST_RESULT(inventory_has_object(inv, 10) == FALSE, "test2_inventory_has_object");
  inventory_destroy(inv);
}

void test1_inventory_get_max() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_get_max(inv) == 5, "test1_inventory_get_max");
  inventory_destroy(inv);
}

void test2_inventory_get_max() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_max(inv) == -1, "test2_inventory_get_max");
}

void test1_inventory_get_objects() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_get_objects(inv) != NULL, "test1_inventory_get_objects");
  inventory_destroy(inv);
}

void test2_inventory_get_objects() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_get_objects(inv) == NULL, "test2_inventory_get_objects");
}

int main() {
  printf("--- INVENTORY TESTS ---\n");
  test1_inventory_create();
  test2_inventory_create();
  test1_inventory_add_object();
  test2_inventory_add_object();
  test1_inventory_del_object();
  test2_inventory_del_object();
  test1_inventory_has_object();
  test2_inventory_has_object();
  test1_inventory_get_max();
  test2_inventory_get_max();
  test1_inventory_get_objects();
  test2_inventory_get_objects();
  
  return 0;
}