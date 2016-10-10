#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_variable_false){
    ck_assert_int_eq(is_variable('C'), false);
} END_TEST

START_TEST(test_is_variable_true){
    ck_assert_int_eq(is_variable('a'), true);
} END_TEST

Suite * make_is_variable_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_variable");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_variable_false);
    tcase_add_test(tc_core, test_is_variable_true);
    suite_add_tcase(s, tc_core);

    return s;
}
