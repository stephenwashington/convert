#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "infix_to_rpn.h"

START_TEST(test_update_infix_stacks_simple){
    struct stack variable_stack = { .content = {0}, .length = 0};
    struct stack symbol_stack = { .content = {0}, .length = 0};
    const char input[] = "a";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_infix_stacks(&variable_stack, &symbol_stack, input[i]);
    }
    
    ck_assert_str_eq((char*)variable_stack.content, "a");
    ck_assert_int_eq(variable_stack.length, 1);
} END_TEST

START_TEST(test_update_infix_stacks_a_b){
    struct stack variable_stack = { .content = {0}, .length = 0};
    struct stack symbol_stack = { .content = {0}, .length = 0};
    const char input[] = "ab";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_infix_stacks(&variable_stack, &symbol_stack, input[i]);
    }
    
    ck_assert_str_eq((char*)variable_stack.content, "ab");
    ck_assert_int_eq(variable_stack.length, 2);
} END_TEST

START_TEST(test_update_infix_stacks_a_plus_b){
    struct stack variable_stack = { .content = {0}, .length = 0};
    struct stack symbol_stack = { .content = {0}, .length = 0};
    const char input[] = "a+b";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_infix_stacks(&variable_stack, &symbol_stack, input[i]);
    }
    char *final_expr = calloc(variable_stack.length + symbol_stack.length + 1,\
                              sizeof(char));

    strcpy(final_expr, (char*)variable_stack.content);
    strcat(final_expr, (char*)symbol_stack.content);
    
    ck_assert_str_eq(final_expr, "ab+");
    ck_assert_int_eq(variable_stack.length + symbol_stack.length, 3);
} END_TEST

Suite * make_update_infix_stacks_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("update_infix_stacks");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_update_infix_stacks_simple);
    tcase_add_test(tc_core, test_update_infix_stacks_a_b);
    tcase_add_test(tc_core, test_update_infix_stacks_a_plus_b);
    suite_add_tcase(s, tc_core);

    return s;
}
