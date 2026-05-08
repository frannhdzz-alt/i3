/**
 * @file set_test.c
 * @author Rodrigo
 * @date 01-05-2026
 * @brief Unit tests for the Set module
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#define PRINT_TEST_RESULT(pass) do { \
    if (pass) printf("[OK] %s:%d\n", __FILE__, __LINE__); \
    else printf("[FAIL] %s:%d\n", __FILE__, __LINE__); \
} while(0)
void test1_set_create() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(s != NULL); 
    set_destroy(s); 
}

void test2_set_create() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_get_n_ids(s) == 0); 
    set_destroy(s); 
}

void test1_set_destroy() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_destroy(s) == OK); 
}

void test2_set_destroy() { 
    Set *s = NULL; 
    PRINT_TEST_RESULT(set_destroy(s) == ERROR); 
}

void test1_set_add() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_add(s, 5) == OK); 
    set_destroy(s); 
}

void test2_set_add() { 
    Set *s = NULL; 
    PRINT_TEST_RESULT(set_add(s, 5) == ERROR); 
}

void test1_set_del() { 
    Set *s = set_create(); 
    set_add(s, 5); 
    PRINT_TEST_RESULT(set_del(s, 5) == OK); 
    set_destroy(s); 
}

void test2_set_del() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_del(s, 5) == ERROR); 
    set_destroy(s); 
}

void test1_set_find() { 
    Set *s = set_create(); 
    set_add(s, 5); 
    PRINT_TEST_RESULT(set_find(s, 5) == TRUE); 
    set_destroy(s); 
}

void test2_set_find() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_find(s, 5) == FALSE); 
    set_destroy(s); 
}

void test1_set_print() { 
    Set *s = set_create(); 
    PRINT_TEST_RESULT(set_print(s) == OK); 
    set_destroy(s); 
}

void test2_set_print() { 
    Set *s = NULL; 
    PRINT_TEST_RESULT(set_print(s) == ERROR); 
}

void test1_set_get_n_ids() { 
    Set *s = set_create(); 
    set_add(s, 5); 
    PRINT_TEST_RESULT(set_get_n_ids(s) == 1); 
    set_destroy(s); 
}

void test2_set_get_n_ids() { 
    Set *s = NULL; 
    PRINT_TEST_RESULT(set_get_n_ids(s) <= 0); 
}

void test1_set_get_id_at() { 
    Set *s = set_create(); 
    set_add(s, 5); 
    PRINT_TEST_RESULT(set_get_id_at(s, 0) == 5); 
    set_destroy(s); 
}

void test2_set_get_id_at() { 
    Set *s = NULL; 
    PRINT_TEST_RESULT(set_get_id_at(s, 0) == NO_ID); 
}

int main() {
    printf("Running SET tests...\n");
    test1_set_create(); test2_set_create();
    test1_set_destroy(); test2_set_destroy();
    test1_set_add(); test2_set_add();
    test1_set_del(); test2_set_del();
    test1_set_find(); test2_set_find();
    test1_set_print(); test2_set_print();
    test1_set_get_n_ids(); test2_set_get_n_ids();
    test1_set_get_id_at(); test2_set_get_id_at();
    return 0;
}