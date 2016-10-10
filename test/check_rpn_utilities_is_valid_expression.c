#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_valid_char_a){
    uint8_t exp[1] = {'a'};
    ck_assert_int_eq(is_valid_expression(exp), true);
} END_TEST

START_TEST(test_is_valid_char_A){
    uint8_t exp[1] = {'A'};
    ck_assert_int_eq(is_valid_expression(exp), false);
} END_TEST

Suite * make_is_valid_expression_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_valid_expression");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_valid_char_a);
    tcase_add_test(tc_core, test_is_valid_char_A);
    suite_add_tcase(s, tc_core);

    return s;
}
