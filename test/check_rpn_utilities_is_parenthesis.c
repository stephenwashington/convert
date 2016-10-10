#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_parenthesis_false){
    ck_assert_int_eq(is_parenthesis('a'), false);
    ck_assert_int_eq(is_parenthesis('R'), false);
    ck_assert_int_eq(is_parenthesis('3'), false);
    ck_assert_int_eq(is_parenthesis('*'), false);
} END_TEST


Suite * make_is_parenthesis_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_parenthesis");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_parenthesis_false);
    suite_add_tcase(s, tc_core);

    return s;
}
