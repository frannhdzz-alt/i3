/**
 * @file character_test.c
 * @author Rodrigo
 * @date 01-05-2026
 * @brief Unit tests for the Character module
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

#define PRINT_TEST_RESULT(pass) do { \
    if (pass) printf("[OK] %s:%d\n", __FILE__, __LINE__); \
    else printf("[FAIL] %s:%d\n", __FILE__, __LINE__); \
} while(0)
void test1_character_create() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(c != NULL); 
    character_destroy(c); 
}

void test2_character_create() { 
    Character *c = character_create(NO_ID); 
    PRINT_TEST_RESULT(c == NULL); 
}

void test1_character_destroy() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_destroy(c) == OK); 
}

void test2_character_destroy() { 
    PRINT_TEST_RESULT(character_destroy(NULL) == ERROR); 
}

void test1_character_get_id() { 
    Character *c = character_create(5); 
    PRINT_TEST_RESULT(character_get_id(c) == 5); 
    character_destroy(c); 
}

void test2_character_get_id() { 
    PRINT_TEST_RESULT(character_get_id(NULL) == NO_ID); 
}

void test1_character_set_name() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_name(c, "Groot") == OK); 
    character_destroy(c); 
}

void test2_character_set_name() { 
    PRINT_TEST_RESULT(character_set_name(NULL, "Groot") == ERROR); 
}

void test1_character_get_name() { 
    Character *c = character_create(1); 
    character_set_name(c, "Groot"); 
    PRINT_TEST_RESULT(strcmp(character_get_name(c), "Groot") == 0); 
    character_destroy(c); 
}

void test2_character_get_name() { 
    PRINT_TEST_RESULT(character_get_name(NULL) == NULL); 
}

void test1_character_set_gdesc() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_gdesc(c, "\\T/") == OK); 
    character_destroy(c); 
}

void test2_character_set_gdesc() { 
    PRINT_TEST_RESULT(character_set_gdesc(NULL, "\\T/") == ERROR); 
}

void test1_character_get_gdesc() { 
    Character *c = character_create(1); 
    character_set_gdesc(c, "\\T/"); 
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "\\T/") == 0); 
    character_destroy(c); 
}

void test2_character_get_gdesc() { 
    PRINT_TEST_RESULT(character_get_gdesc(NULL) == NULL); 
}

void test1_character_set_health() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_health(c, 10) == OK); 
    character_destroy(c); 
}

void test2_character_set_health() { 
    PRINT_TEST_RESULT(character_set_health(NULL, 10) == ERROR); 
}

void test1_character_get_health() { 
    Character *c = character_create(1); 
    character_set_health(c, 10); 
    PRINT_TEST_RESULT(character_get_health(c) == 10); 
    character_destroy(c); 
}

void test2_character_get_health() { 
    PRINT_TEST_RESULT(character_get_health(NULL) == -1); 
}

void test1_character_set_friendly() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK); 
    character_destroy(c); 
}

void test2_character_set_friendly() { 
    PRINT_TEST_RESULT(character_set_friendly(NULL, TRUE) == ERROR); 
}

void test1_character_get_friendly() { 
    Character *c = character_create(1); 
    character_set_friendly(c, TRUE); 
    PRINT_TEST_RESULT(character_get_friendly(c) == TRUE); 
    character_destroy(c); 
}

void test2_character_get_friendly() { 
    PRINT_TEST_RESULT(character_get_friendly(NULL) == FALSE); 
}

void test1_character_set_message() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_message(c, "I am Groot") == OK); 
    character_destroy(c); 
}

void test2_character_set_message() { 
    PRINT_TEST_RESULT(character_set_message(NULL, "I am Groot") == ERROR); 
}

void test1_character_get_message() { 
    Character *c = character_create(1); 
    character_set_message(c, "Hi"); 
    PRINT_TEST_RESULT(strcmp(character_get_message(c), "Hi") == 0); 
    character_destroy(c); 
}

void test2_character_get_message() { 
    PRINT_TEST_RESULT(character_get_message(NULL) == NULL); 
}

void test1_character_print() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_print(c) == OK); 
    character_destroy(c); 
}

void test2_character_print() { 
    PRINT_TEST_RESULT(character_print(NULL) == ERROR); 
}

void test1_character_set_following() { 
    Character *c = character_create(1); 
    PRINT_TEST_RESULT(character_set_following(c, 2) == OK); 
    character_destroy(c); 
}

void test2_character_set_following() { 
    PRINT_TEST_RESULT(character_set_following(NULL, 2) == ERROR); 
}

void test1_character_get_following() { 
    Character *c = character_create(1); 
    character_set_following(c, 2); 
    PRINT_TEST_RESULT(character_get_following(c) == 2); 
    character_destroy(c); 
}

void test2_character_get_following() { 
    PRINT_TEST_RESULT(character_get_following(NULL) == NO_ID); 
}

int main() {
    printf("Running CHARACTER tests...\n");
    test1_character_create(); test2_character_create();
    test1_character_destroy(); test2_character_destroy();
    test1_character_get_id(); test2_character_get_id();
    test1_character_set_name(); test2_character_set_name();
    test1_character_get_name(); test2_character_get_name();
    test1_character_set_gdesc(); test2_character_set_gdesc();
    test1_character_get_gdesc(); test2_character_get_gdesc();
    test1_character_set_health(); test2_character_set_health();
    test1_character_get_health(); test2_character_get_health();
    test1_character_set_friendly(); test2_character_set_friendly();
    test1_character_get_friendly(); test2_character_get_friendly();
    test1_character_set_message(); test2_character_set_message();
    test1_character_get_message(); test2_character_get_message();
    test1_character_print(); test2_character_print();
    test1_character_set_following(); test2_character_set_following();
    test1_character_get_following(); test2_character_get_following();
    return 0;
}