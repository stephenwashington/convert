#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "rpn_to_infix.h"

START_TEST(test_rpn_to_infix_simple){
    ck_assert_str_eq(rpn_to_infix("a"), "a");
} END_TEST

START_TEST(test_rpn_to_infix_a_plus_b){
    ck_assert_str_eq(rpn_to_infix("ab+"), "(a+b)");
} END_TEST

START_TEST(test_rpn_to_infix_ab_throw_error){
    rpn_to_infix("ab");
} END_TEST

Suite * make_rpn_to_infix_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_to_infix");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_to_infix_simple);
    tcase_add_test(tc_core, test_rpn_to_infix_a_plus_b);
    tcase_add_exit_test(tc_core, test_rpn_to_infix_ab_throw_error,EXIT_FAILURE);
    suite_add_tcase(s, tc_core);

    return s;
}
