/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Maria
 * @version 2.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#include "set.h"
#include <stdio.h>
#include <stdlib.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL, "test1_set_create");
  set_destroy(s);
}

void test2_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_find(s, 5) == FALSE, "test2_set_create");
  set_destroy(s);
}

void test1_set_add() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add(s, 5) == OK, "test1_set_add");
  set_destroy(s);
}

void test2_set_add() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add(s, 5) == ERROR, "test2_set_add");
}

void test1_set_del() {
  Set *s = set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(set_del(s, 5) == OK, "test1_set_del");
  set_destroy(s);
}

void test2_set_del() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_del(s, 5) == ERROR, "test2_set_del"); 
  set_destroy(s);
}

void test1_set_find() {
  Set *s = set_create();
  set_add(s, 10);
  PRINT_TEST_RESULT(set_find(s, 10) == TRUE, "test1_set_find");
  set_destroy(s);
}

void test2_set_find() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_find(s, 10) == FALSE, "test2_set_find"); 
  set_destroy(s);
}

void test1_set_get_n_ids() {
  Set *s = set_create();
  set_add(s, 10);
  PRINT_TEST_RESULT(set_get_n_ids(s) == 1, "test1_set_get_n_ids");
  set_destroy(s);
}

void test2_set_get_n_ids() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_n_ids(s) == 0, "test2_set_get_n_ids");
}

void test1_set_get_id_at() {
  Set *s = set_create();
  set_add(s, 20);
  PRINT_TEST_RESULT(set_get_id_at(s, 0) == 20, "test1_set_get_id_at");
  set_destroy(s);
}

void test2_set_get_id_at() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_id_at(s, 0) == NO_ID, "test2_set_get_id_at");
}

int main() {
  printf("--- SET TESTS ---\n");
  test1_set_create();
  test2_set_create();
  test1_set_add();
  test2_set_add();
  test1_set_del();
  test2_set_del();
  test1_set_find();
  test2_set_find();
  test1_set_get_n_ids();
  test2_set_get_n_ids();
  test1_set_get_id_at();
  test2_set_get_id_at();
  return 0;
}