/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author Rodrigo y Mario
 * @version 1.0
 * @date 13-03-2026
 * @copyright GNU Public License
 */

#include "character.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_character_create() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(c != NULL, "test1_character_create");
  character_destroy(c);
}

void test2_character_create() {
  Character *c = character_create(NO_ID);
  PRINT_TEST_RESULT(c == NULL, "test2_character_create");
}

void test1_character_get_id() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_get_id(c) == 5, "test1_character_get_id");
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID, "test2_character_get_id");
}

void test1_character_set_name() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_name(c, "Goblin") == OK, "test1_character_set_name");
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "Goblin") == ERROR, "test2_character_set_name");
}

void test1_character_set_gdesc() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_gdesc(c, "\\Oo/") == OK, "test1_character_set_gdesc");
  character_destroy(c);
}

void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "\\Oo/") == ERROR, "test2_character_set_gdesc");
}

void test1_character_set_health() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_health(c, 10) == OK, "test1_character_set_health");
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_health(c, -5) == ERROR, "test2_character_set_health");
  character_destroy(c);
}

void test1_character_set_friendly() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK, "test1_character_set_friendly");
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR, "test2_character_set_friendly");
}

void test1_character_set_message() {
  Character *c = character_create(5);
  PRINT_TEST_RESULT(character_set_message(c, "Hello!") == OK, "test1_character_set_message");
  character_destroy(c);
}

void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "Hello!") == ERROR, "test2_character_set_message");
}

int main() {
  printf("--- CHARACTER TESTS ---\n");
  test1_character_create();
  test2_character_create();
  test1_character_get_id();
  test2_character_get_id();
  test1_character_set_name();
  test2_character_set_name();
  test1_character_set_gdesc();
  test2_character_set_gdesc();
  test1_character_set_health();
  test2_character_set_health();
  test1_character_set_friendly();
  test2_character_set_friendly();
  test1_character_set_message();
  test2_character_set_message();
  return 0;
}