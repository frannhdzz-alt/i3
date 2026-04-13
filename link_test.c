/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @author María Gómez
 * @version 2.0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_link_create() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(l != NULL, "test1_link_create");
  link_destroy(l);
}

void test2_link_create() {
  Link *l = link_create(NO_ID);
  PRINT_TEST_RESULT(l == NULL, "test2_link_create");
}

void test1_link_set_name() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_set_name(l, "Puerta") == OK, "test1_link_set_name");
  link_destroy(l);
}

void test2_link_set_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_name(l, "Puerta") == ERROR, "test2_link_set_name");
}

void test1_link_set_origin() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_set_origin(l, 11) == OK, "test1_link_set_origin");
  link_destroy(l);
}

void test2_link_set_origin() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_origin(l, 11) == ERROR, "test2_link_set_origin");
}

void test1_link_set_destination() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_set_destination(l, 12) == OK, "test1_link_set_destination");
  link_destroy(l);
}

void test2_link_set_destination() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_destination(l, 12) == ERROR, "test2_link_set_destination");
}

void test1_link_set_direction() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_set_direction(l, S) == OK, "test1_link_set_direction");
  link_destroy(l);
}

void test2_link_set_direction() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_direction(l, S) == ERROR, "test2_link_set_direction");
}

void test1_link_set_open() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK, "test1_link_set_open");
  link_destroy(l);
}

void test2_link_set_open() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == ERROR, "test2_link_set_open");
}

void test1_link_get_id() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_get_id(l) == 5, "test1_link_get_id");
  link_destroy(l);
}

void test2_link_get_id() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_id(l) == NO_ID, "test2_link_get_id");
}

void test1_link_get_name() {
  Link *l = link_create(5);
  link_set_name(l, "Puerta");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "Puerta") == 0, "test1_link_get_name");
  link_destroy(l);
}

void test2_link_get_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_name(l) == NULL, "test2_link_get_name");
}

void test1_link_get_origin() {
  Link *l = link_create(5);
  link_set_origin(l, 11);
  PRINT_TEST_RESULT(link_get_origin(l) == 11, "test1_link_get_origin");
  link_destroy(l);
}

void test2_link_get_origin() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_origin(l) == NO_ID, "test2_link_get_origin");
}

void test1_link_get_destination() {
  Link *l = link_create(5);
  link_set_destination(l, 12);
  PRINT_TEST_RESULT(link_get_destination(l) == 12, "test1_link_get_destination");
  link_destroy(l);
}

void test2_link_get_destination() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_destination(l) == NO_ID, "test2_link_get_destination");
}

void test1_link_get_direction() {
  Link *l = link_create(5);
  link_set_direction(l, E);
  PRINT_TEST_RESULT(link_get_direction(l) == E, "test1_link_get_direction");
  link_destroy(l);
}

void test2_link_get_direction() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_direction(l) == N, "test2_link_get_direction");
}

void test1_link_get_open() {
  Link *l = link_create(5);
  link_set_open(l, TRUE);
  PRINT_TEST_RESULT(link_get_open(l) == TRUE, "test1_link_get_open");
  link_destroy(l);
}

void test2_link_get_open() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_open(l) == FALSE, "test2_link_get_open");
}

int main() {
  printf("--- LINK TESTS ---\n");
  test1_link_create();
  test2_link_create();
  test1_link_set_name();
  test2_link_set_name();
  test1_link_set_origin();
  test2_link_set_origin();
  test1_link_set_destination();
  test2_link_set_destination();
  test1_link_set_direction();
  test2_link_set_direction();
  test1_link_set_open();
  test2_link_set_open();
  test1_link_get_id();
  test2_link_get_id();
  test1_link_get_name();
  test2_link_get_name();
  test1_link_get_origin();
  test2_link_get_origin();
  test1_link_get_destination();
  test2_link_get_destination();
  test1_link_get_direction();
  test2_link_get_direction();
  test1_link_get_open();
  test2_link_get_open();
  return 0;
}