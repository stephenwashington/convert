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

START_TEST(test_convert_infix_to_rpn_stacks_a_plus_b_minus_c){
    ck_assert_str_eq(infix_to_rpn("a+b-c"), "abc-+");
} END_TEST

START_TEST(test_convert_infix_to_rpn_obey_order_of_operations){
    ck_assert_str_eq(infix_to_rpn("l/m^n*o-p"), "lmn^/o*p-");
} END_TEST

START_TEST(test_convert_infix_to_rpn_expr_with_parentheses){
    ck_assert_str_eq(infix_to_rpn("((v/w)^x)*(y-z)"), "vw/x^yz-*");
} END_TEST

START_TEST(test_convert_infix_to_rpn_complex_expression){
    ck_assert_str_eq(infix_to_rpn("(a+g)*(((b-a)+c)^(c+(e*(d^f)))))"),\
                                   "ag+ba-c+cedf^*+^*"); 
} END_TEST


Suite * make_convert_infix_to_rpn_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("convert_infix_to_rpn");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_convert_infix_to_rpn_stacks_simple);
    tcase_add_test(tc_core, test_convert_infix_to_rpn_stacks_a_plus_b);
    tcase_add_test(tc_core, test_convert_infix_to_rpn_stacks_a_plus_b_minus_c);
    tcase_add_test(tc_core,\
                   test_convert_infix_to_rpn_obey_order_of_operations);
    tcase_add_test(tc_core, test_convert_infix_to_rpn_expr_with_parentheses);
    tcase_add_test(tc_core, test_convert_infix_to_rpn_complex_expression);
    suite_add_tcase(s, tc_core);

    return s;
}
