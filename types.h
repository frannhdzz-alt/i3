/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Rodrigo y Mario
 * @version 2.0
 * @date 13-03-2026
 * @copyright GNU Public License
 */

#include "space.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_space_create() {
  Space *s = space_create(5);
  PRINT_TEST_RESULT(s != NULL, "test1_space_create");
  space_destroy(s);
}

void test2_space_create() {
  Space *s = space_create(NO_ID);
  PRINT_TEST_RESULT(s == NULL, "test2_space_create");
}

void test1_space_add_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_object(s, 10) == OK, "test1_space_add_object");
  space_destroy(s);
}

void test2_space_add_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR, "test2_space_add_object");
}

void test1_space_has_object() {
  Space *s = space_create(1);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_has_object(s, 10) == TRUE, "test1_space_has_object");
  space_destroy(s);
}

void test2_space_has_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_has_object(s, 10) == FALSE, "test2_space_has_object");
  space_destroy(s);
}

void test1_space_set_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc(s, 0, "---------") == OK, "test1_space_set_gdesc");
  space_destroy(s);
}

void test2_space_set_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc(s, 5, "---------") == ERROR, "test2_space_set_gdesc"); 
  space_destroy(s);
}

void test1_space_set_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_character(s, 22) == OK, "test1_space_set_character");
  space_destroy(s);
}

void test2_space_set_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_character(s, 22) == ERROR, "test2_space_set_character");
}

int main() {
  printf("--- SPACE TESTS ---\n");
  test1_space_create();
  test2_space_create();
  test1_space_add_object();
  test2_space_add_object();
  test1_space_has_object();
  test2_space_has_object();
  test1_space_set_gdesc();
  test2_space_set_gdesc();
  test1_space_set_character();
  test2_space_set_character();
  return 0;
}