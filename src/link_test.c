/**
 * @file link_test.c
 * @author Rodrigo
 * @date 01-05-2026
 * @brief Unit tests for the Link module
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#define PRINT_TEST_RESULT(pass) do { \
    if (pass) printf("[OK] %s:%d\n", __FILE__, __LINE__); \
    else printf("[FAIL] %s:%d\n", __FILE__, __LINE__); \
} while(0)

void test1_link_create() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(l != NULL); 
    link_destroy(l); 
}

void test2_link_create() { 
    Link *l = link_create(NO_ID); 
    PRINT_TEST_RESULT(l == NULL); 
}

void test1_link_destroy() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_destroy(l) == OK); 
}

void test2_link_destroy() { 
    Link *l = NULL; 
    PRINT_TEST_RESULT(link_destroy(l) == ERROR); 
}

void test1_link_set_name() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_name(l, "Door") == OK); 
    link_destroy(l); 
}

void test2_link_set_name() { 
    PRINT_TEST_RESULT(link_set_name(NULL, "Door") == ERROR); 
}

void test1_link_set_origin() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_origin(l, 10) == OK); 
    link_destroy(l); 
}

void test2_link_set_origin() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_origin(l, NO_ID) == ERROR); 
    link_destroy(l); 
}

void test1_link_set_destination() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_destination(l, 20) == OK); 
    link_destroy(l); 
}

void test2_link_set_destination() { 
    PRINT_TEST_RESULT(link_set_destination(NULL, 20) == ERROR); 
}

void test1_link_set_direction() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_direction(l, N) == OK); 
    link_destroy(l); 
}

void test2_link_set_direction() { 
    PRINT_TEST_RESULT(link_set_direction(NULL, N) == ERROR); 
}

void test1_link_set_open() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK); 
    link_destroy(l); 
}

void test2_link_set_open() { 
    PRINT_TEST_RESULT(link_set_open(NULL, TRUE) == ERROR); 
}

void test1_link_get_id() { 
    Link *l = link_create(5); 
    PRINT_TEST_RESULT(link_get_id(l) == 5); 
    link_destroy(l); 
}

void test2_link_get_id() { 
    PRINT_TEST_RESULT(link_get_id(NULL) == NO_ID); 
}

void test1_link_get_name() { 
    Link *l = link_create(1); 
    link_set_name(l, "Door"); 
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "Door") == 0); 
    link_destroy(l); 
}

void test2_link_get_name() { 
    PRINT_TEST_RESULT(link_get_name(NULL) == NULL); 
}

void test1_link_get_origin() { 
    Link *l = link_create(1); 
    link_set_origin(l, 10); 
    PRINT_TEST_RESULT(link_get_origin(l) == 10); 
    link_destroy(l); 
}

void test2_link_get_origin() { 
    PRINT_TEST_RESULT(link_get_origin(NULL) == NO_ID); 
}

void test1_link_get_destination() { 
    Link *l = link_create(1); 
    link_set_destination(l, 20); 
    PRINT_TEST_RESULT(link_get_destination(l) == 20); 
    link_destroy(l); 
}

void test2_link_get_destination() { 
    PRINT_TEST_RESULT(link_get_destination(NULL) == NO_ID); 
}

void test1_link_get_direction() { 
    Link *l = link_create(1); 
    link_set_direction(l, N); 
    PRINT_TEST_RESULT(link_get_direction(l) == N); 
    link_destroy(l); 
}

void test2_link_get_direction() { 
    PRINT_TEST_RESULT(link_get_direction(NULL) == DIR_UNKNOWN); 
}

void test1_link_get_open() { 
    Link *l = link_create(1); 
    link_set_open(l, TRUE); 
    PRINT_TEST_RESULT(link_get_open(l) == TRUE); 
    link_destroy(l); 
}

void test2_link_get_open() { 
    PRINT_TEST_RESULT(link_get_open(NULL) == FALSE); 
}

void test1_link_print() { 
    Link *l = link_create(1); 
    PRINT_TEST_RESULT(link_print(l) == OK); 
    link_destroy(l); 
}

void test2_link_print() { 
    PRINT_TEST_RESULT(link_print(NULL) == ERROR); 
}

int main() {
    printf("Running LINK tests...\n");
    test1_link_create(); test2_link_create();
    test1_link_destroy(); test2_link_destroy();
    test1_link_set_name(); test2_link_set_name();
    test1_link_set_origin(); test2_link_set_origin();
    test1_link_set_destination(); test2_link_set_destination();
    test1_link_set_direction(); test2_link_set_direction();
    test1_link_set_open(); test2_link_set_open();
    test1_link_get_id(); test2_link_get_id();
    test1_link_get_name(); test2_link_get_name();
    test1_link_get_origin(); test2_link_get_origin();
    test1_link_get_destination(); test2_link_get_destination();
    test1_link_get_direction(); test2_link_get_direction();
    test1_link_get_open(); test2_link_get_open();
    test1_link_print(); test2_link_print();
    return 0;
}