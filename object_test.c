/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @author Maria
 * @version 1.0
 * @date 24-03-2026
 * @copyright GNU Public License
 */

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_object_create() {
  Object *o = object_create(5);
  PRINT_TEST_RESULT(o != NULL, "test1_object_create");
  object_destroy(o);
}

void test2_object_create() {
  Object *o = object_create(NO_ID);
  PRINT_TEST_RESULT(o == NULL, "test2_object_create");
}

void test1_object_get_id() {
  Object *o = object_create(25);
  PRINT_TEST_RESULT(object_get_id(o) == 25, "test1_object_get_id");
  object_destroy(o);
}

void test2_object_get_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID, "test2_object_get_id");
}

void test1_object_set_name() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_name(o, "test_obj") == OK, "test1_object_set_name");
  object_destroy(o);
}

void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "test_obj") == ERROR, "test2_object_set_name");
}

void test1_object_get_name() {
  Object *o = object_create(1);
  object_set_name(o, "test_obj");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "test_obj") == 0, "test1_object_get_name");
  object_destroy(o);
}

void test1_object_set_description() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_description(o, "test_desc") == OK, "test1_object_set_description");
  object_destroy(o);
}

void test2_object_set_description() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_description(o, "test_desc") == ERROR, "test2_object_set_description");
}

void test1_object_get_description() {
  Object *o = object_create(1);
  object_set_description(o, "test_desc");
  PRINT_TEST_RESULT(strcmp(object_get_description(o), "test_desc") == 0, "test1_object_get_description");
  object_destroy(o);
}

int main() {
  printf("--- OBJECT TESTS ---\n");
  test1_object_create();
  test2_object_create();
  test1_object_get_id();
  test2_object_get_id();
  test1_object_set_name();
  test2_object_set_name();
  test1_object_get_name();
  test1_object_set_description();
  test2_object_set_description();
  test1_object_get_description();
  return 0;
}