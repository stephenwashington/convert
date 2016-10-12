#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "rpn_to_infix.h"

START_TEST(test_update_rpn_stack_simple){
    uint8_t stack[50][1000];
    int16_t stack_length = 0;
    const char input[] = "a";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_rpn_stack(stack, &stack_length, input[i]);
    }
    
    ck_assert_int_eq(stack[0][0], 'a');
} END_TEST

START_TEST(test_update_rpn_stack_a_then_b){
    uint8_t stack[50][1000];
    int16_t stack_length = 0;
    const char input[] = "ab";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_rpn_stack(stack, &stack_length, input[i]);
    }
    
    ck_assert_int_eq(stack[0][0], 'a');
    ck_assert_int_eq(stack[1][0], 'b');
} END_TEST

START_TEST(test_update_rpn_stack_add_b_to_a){
    uint8_t stack[50][1000];
    int16_t stack_length = 0;
    const char input[] = "ab+";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_rpn_stack(stack, &stack_length, input[i]);
    }
    
    ck_assert_int_eq(stack[0][0], 'a');
    ck_assert_int_eq(stack[0][1], '+');
    ck_assert_int_eq(stack[0][2], 'b');
} END_TEST


Suite * make_update_rpn_stack_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("update_rpn_stack");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_update_rpn_stack_simple);
    tcase_add_test(tc_core, test_update_rpn_stack_a_then_b);
    tcase_add_test(tc_core, test_update_rpn_stack_add_b_to_a);
    suite_add_tcase(s, tc_core);

    return s;
}
