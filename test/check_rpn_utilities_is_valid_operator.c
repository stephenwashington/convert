#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_valid_operator_false){
    ck_assert_int_eq(is_valid_operator('c'), false);
    ck_assert_int_eq(is_valid_operator('Y'), false);
    ck_assert_int_eq(is_valid_operator('%'), false);
    ck_assert_int_eq(is_valid_operator('('), false);
} END_TEST

START_TEST(test_is_valid_operator_true){
    ck_assert_int_eq(is_valid_operator('+'), true);
    ck_assert_int_eq(is_valid_operator('-'), true);
    ck_assert_int_eq(is_valid_operator('*'), true);
    ck_assert_int_eq(is_valid_operator('/'), true);
    ck_assert_int_eq(is_valid_operator('^'), true);
} END_TEST


Suite * make_is_valid_operator_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_valid_operator");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_valid_operator_false);
    tcase_add_test(tc_core, test_is_valid_operator_true);
    suite_add_tcase(s, tc_core);

    return s;
}