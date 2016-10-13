#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_symbol_false){
    ck_assert_int_eq(is_symbol('a'), false);
    ck_assert_int_eq(is_symbol('R'), false);
    ck_assert_int_eq(is_symbol('3'), false);
    
} END_TEST

START_TEST(test_is_symbol_true){
    ck_assert_int_eq(is_symbol('('), true);
    ck_assert_int_eq(is_symbol('+'), true);
    ck_assert_int_eq(is_symbol('*'), false);
} END_TEST


Suite * make_is_symbol_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_symbol");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_symbol_false);
    tcase_add_test(tc_core, test_is_symbol_true);
    suite_add_tcase(s, tc_core);

    return s;
}
