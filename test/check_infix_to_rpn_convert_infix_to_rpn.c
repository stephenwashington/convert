#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "infix_to_rpn.h"

START_TEST(test_convert_infix_to_rpn_stacks_simple){
    ck_assert_str_eq(infix_to_rpn("a"), "a");
} END_TEST

START_TEST(test_convert_infix_to_rpn_stacks_a_plus_b){
    ck_assert_str_eq(infix_to_rpn("a+b"), "ab+");
} END_TEST




Suite * make_convert_infix_to_rpn_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("convert_infix_to_rpn");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_convert_infix_to_rpn_stacks_simple);
    tcase_add_test(tc_core, test_convert_infix_to_rpn_stacks_a_plus_b);
    suite_add_tcase(s, tc_core);

    return s;
}
