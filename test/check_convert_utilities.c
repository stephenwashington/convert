#include <check.h>
#include <stdbool.h>
#include "utilities.h"
#include "unit_tests.h"

START_TEST(test_rpn_utilities_a){
    ck_assert_int_eq(is_variable('a'), true);
    ck_assert_int_eq(is_operator('a'), false);
    ck_assert_int_eq(is_parenthesis('a'), false);
    ck_assert_int_eq(is_symbol('a'), false);
    ck_assert_int_eq(is_valid_char('a'), true);
    ck_assert_int_eq(is_right_associative('a'), false);
    ck_assert_int_eq(operator_precedence('a'), 6);
} END_TEST

START_TEST(test_rpn_utilities_A){
    ck_assert_int_eq(is_variable('A'), false);
    ck_assert_int_eq(is_operator('A'), false);
    ck_assert_int_eq(is_parenthesis('A'), false);
    ck_assert_int_eq(is_symbol('A'), false);
    ck_assert_int_eq(is_valid_char('A'), false);
    ck_assert_int_eq(is_right_associative('A'), false);
    ck_assert_int_eq(operator_precedence('A'), 6);
} END_TEST

START_TEST(test_rpn_utilities_number){
    ck_assert_int_eq(is_variable('3'), false);
    ck_assert_int_eq(is_operator('3'), false);
    ck_assert_int_eq(is_parenthesis('3'), false);
    ck_assert_int_eq(is_symbol('3'), false);
    ck_assert_int_eq(is_valid_char('3'), false);
    ck_assert_int_eq(is_right_associative('3'), false);
    ck_assert_int_eq(operator_precedence('3'), 6);
} END_TEST

START_TEST(test_rpn_utilities_plus){
    ck_assert_int_eq(is_variable('+'), false);
    ck_assert_int_eq(is_operator('+'), true);
    ck_assert_int_eq(is_parenthesis('+'), false);
    ck_assert_int_eq(is_symbol('+'), true);
    ck_assert_int_eq(is_valid_char('+'), true);
    ck_assert_int_eq(is_right_associative('+'), false);
    ck_assert_int_eq(operator_precedence('+'), 5);
} END_TEST

START_TEST(test_rpn_utilities_exponent){
    ck_assert_int_eq(is_variable('^'), false);
    ck_assert_int_eq(is_operator('^'), true);
    ck_assert_int_eq(is_parenthesis('^'), false);
    ck_assert_int_eq(is_symbol('^'), true);
    ck_assert_int_eq(is_valid_char('^'), true);
    ck_assert_int_eq(is_right_associative('^'), true);
    ck_assert_int_eq(operator_precedence('^'), 1);
} END_TEST

START_TEST(test_rpn_utilities_left_paren){
    ck_assert_int_eq(is_variable('('), false);
    ck_assert_int_eq(is_operator('('), false);
    ck_assert_int_eq(is_parenthesis('('), true);
    ck_assert_int_eq(is_symbol('('), true);
    ck_assert_int_eq(is_valid_char('('), true);
    ck_assert_int_eq(is_right_associative('('), false);
    ck_assert_int_eq(operator_precedence('('), 6);
} END_TEST

START_TEST(test_rpn_utilities_percent){
    ck_assert_int_eq(is_variable('%'), false);
    ck_assert_int_eq(is_operator('%'), false);
    ck_assert_int_eq(is_parenthesis('%'), false);
    ck_assert_int_eq(is_symbol('%'), false);
    ck_assert_int_eq(is_valid_char('%'), false);
    ck_assert_int_eq(is_right_associative('%'), false);
    ck_assert_int_eq(operator_precedence('%'), 6);
} END_TEST

Suite * make_rpn_utilities_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_utilities");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_utilities_a);
    tcase_add_test(tc_core, test_rpn_utilities_A);
    tcase_add_test(tc_core, test_rpn_utilities_plus);
    tcase_add_test(tc_core, test_rpn_utilities_number);
    tcase_add_test(tc_core, test_rpn_utilities_exponent);
    tcase_add_test(tc_core, test_rpn_utilities_left_paren);
    tcase_add_test(tc_core, test_rpn_utilities_percent);
    suite_add_tcase(s, tc_core);

    return s;
}
