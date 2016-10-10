#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_valid_expression_a){
    uint8_t exp[1] = {'a'};
    ck_assert_int_eq(is_valid_expression(exp), true);
} END_TEST

START_TEST(test_is_valid_expression_A){
    uint8_t exp[1] = {'A'};
    ck_assert_int_eq(is_valid_expression(exp), false);
} END_TEST

START_TEST(test_is_valid_expression_aplusb){
    uint8_t exp[3] = {'a', '+', 'b'};
    ck_assert_int_eq(is_valid_expression(exp), true);
} END_TEST

/*START_TEST(test_is_valid_expression_ab){
    uint8_t exp[2] = {'a', 'b'};
    ck_assert_int_eq(is_valid_expression(exp), false);
} END_TEST */

Suite * make_is_valid_expression_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_valid_expression");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_valid_expression_a);
    tcase_add_test(tc_core, test_is_valid_expression_A);
    tcase_add_test(tc_core, test_is_valid_expression_aplusb);
    //tcase_add_test(tc_core, test_is_valid_expression_ab);
    suite_add_tcase(s, tc_core);

    return s;
}
