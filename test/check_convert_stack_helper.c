#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utilities.h"
#include "unit_tests.h"

START_TEST(test_rpn_stack_append_single){
    struct stack s = { .content = {0}, .length = 0};
    append(&s, 'a');
    ck_assert_int_eq(s.content[0], 'a');
    ck_assert_int_eq(s.length, 1);
} END_TEST

START_TEST(test_rpn_stack_append_multiple){
    struct stack s = { .content = {0}, .length = 0};
    const char * input = "ab";
    for (uint16_t i = 0; i < strlen(input); i++){
        append(&s, input[i]);
    }
    ck_assert_int_eq(s.content[0], 'a');
    ck_assert_int_eq(s.content[1], 'b');
    ck_assert_int_eq(s.length, 2);
} END_TEST

START_TEST(test_rpn_stack_append_invalid_characters){
    struct stack s = { .content = {0}, .length = 0};
    const char * input = "aBc";
    for (uint16_t i = 0; i < strlen(input); i++){
        append(&s, input[i]);
    }
} END_TEST

START_TEST(test_rpn_stack_append_overflow){
    struct stack s = { .content = {0}, .length = 0};
    const char * input = "a";
    for (uint16_t i = 0; i < 1001; i++){
        append(&s, input[0]);
    }
} END_TEST

START_TEST(test_rpn_stack_append_normal_input){
    struct stack s = { .content = {0}, .length = 0};
    const char * input = "(a+g)*(((b-a)+c)^(c+(e*(d^f))))";
    for (uint16_t i = 0; i < strlen(input); i++){
        append(&s, input[i]);
    }
    ck_assert_int_eq(s.length, 31);
} END_TEST

START_TEST(test_rpn_stack_pop_single){
    struct stack s = { .content = {0}, .length = 0};
    append(&s, 'a');
    pop(&s);
    ck_assert_int_eq(s.content[0], '\0');
    ck_assert_int_eq(s.length, 0);
} END_TEST

START_TEST(test_rpn_stack_pop_empty){
    struct stack s = { .content = {0}, .length = 0};
    pop(&s);
} END_TEST


Suite * make_rpn_stack_helper_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_stack_helper");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_stack_append_single);
    tcase_add_test(tc_core, test_rpn_stack_append_multiple);
    tcase_add_exit_test(tc_core,\
                        test_rpn_stack_append_invalid_characters,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core,\
                        test_rpn_stack_append_overflow,\
                        EXIT_FAILURE);
    tcase_add_test(tc_core, test_rpn_stack_append_normal_input);
    tcase_add_test(tc_core, test_rpn_stack_pop_single);
    tcase_add_exit_test(tc_core, test_rpn_stack_pop_empty,\
                        EXIT_FAILURE);
    suite_add_tcase(s, tc_core);

    return s;
}
