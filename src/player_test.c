/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @author Maria
 * @version 1.0
 * @date 13-04-2026
 * @copyright GNU Public License
 */

#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_TEST_RESULT(pass, name) \
  do { \
    fprintf(stdout, "%s : %s\n", (name), (pass) ? "OK" : "FAIL"); \
  } while (0)

void test1_player_create() {
  Player *p = player_create(5);
  PRINT_TEST_RESULT(p != NULL, "test1_player_create");
  player_destroy(p);
}

void test2_player_create() {
  Player *p = player_create(NO_ID);
  PRINT_TEST_RESULT(p == NULL, "test2_player_create");
}

void test1_player_set_name() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_name(p, "test_player") == OK, "test1_player_set_name");
  player_destroy(p);
}

void test2_player_set_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_name(p, "test_player") == ERROR, "test2_player_set_name");
}

void test1_player_get_name() {
  Player *p = player_create(1);
  player_set_name(p, "test_player");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "test_player") == 0, "test1_player_get_name");
  player_destroy(p);
}

void test1_player_set_location() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_location(p, 11) == OK, "test1_player_set_location");
  player_destroy(p);
}

void test2_player_set_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_location(p, 11) == ERROR, "test2_player_set_location");
}

void test1_player_get_location() {
  Player *p = player_create(1);
  player_set_location(p, 11);
  PRINT_TEST_RESULT(player_get_location(p) == 11, "test1_player_get_location");
  player_destroy(p);
}

void test1_player_add_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_add_object(p, 10) == OK, "test1_player_add_object");
  player_destroy(p);
}

void test2_player_add_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_add_object(p, 10) == ERROR, "test2_player_add_object");
}

void test1_player_has_object() {
  Player *p = player_create(1);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_has_object(p, 10) == TRUE, "test1_player_has_object");
  player_destroy(p);
}

void test2_player_has_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_has_object(p, 10) == FALSE, "test2_player_has_object");
  player_destroy(p);
}

void test1_player_del_object() {
  Player *p = player_create(1);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_del_object(p, 10) == OK, "test1_player_del_object");
  player_destroy(p);
}

void test1_player_get_inventory() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_get_inventory(p) != NULL, "test1_player_get_inventory");
  player_destroy(p);
}

void test1_player_set_health() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_health(p, 10) == OK, "test1_player_set_health");
  player_destroy(p);
}

void test2_player_set_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_health(p, 10) == ERROR, "test2_player_set_health");
}

void test1_player_get_health() {
  Player *p = player_create(1);
  player_set_health(p, 8);
  PRINT_TEST_RESULT(player_get_health(p) == 8, "test1_player_get_health");
  player_destroy(p);
}

void test1_player_set_gdesc() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_gdesc(p, "test_g") == OK, "test1_player_set_gdesc");
  player_destroy(p);
}

void test2_player_set_gdesc() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_gdesc(p, "test_g") == ERROR, "test2_player_set_gdesc");
}

void test1_player_get_gdesc() {
  Player *p = player_create(1);
  player_set_gdesc(p, "test_g");
  PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "test_g") == 0, "test1_player_get_gdesc");
  player_destroy(p);
}

int main() {
  printf("--- PLAYER TESTS ---\n");
  test1_player_create();
  test2_player_create();
  test1_player_set_name();
  test2_player_set_name();
  test1_player_get_name();
  test1_player_set_location();
  test2_player_set_location();
  test1_player_get_location();
  test1_player_add_object();
  test2_player_add_object();
  test1_player_has_object();
  test2_player_has_object();
  test1_player_del_object();
  test1_player_get_inventory();
  test1_player_set_health();
  test2_player_set_health();
  test1_player_get_health();
  test1_player_set_gdesc();
  test2_player_set_gdesc();
  test1_player_get_gdesc();
  return 0;
}