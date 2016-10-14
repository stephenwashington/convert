#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_valid_expression_a){
    ck_assert_int_eq(is_valid_expression("a"), true);
} END_TEST

START_TEST(test_is_valid_expression_A){
    ck_assert_int_eq(is_valid_expression("A"), false);
} END_TEST

START_TEST(test_is_valid_expression_aplusb){
    ck_assert_int_eq(is_valid_expression("a+b"), true);
} END_TEST

START_TEST(test_is_valid_expression_ab){
    ck_assert_int_eq(is_valid_expression("ab"), false);
} END_TEST

START_TEST(test_is_valid_expression_negb){
    ck_assert_int_eq(is_valid_expression("-b"), false);
} END_TEST

START_TEST(test_is_valid_expression_complex){
    ck_assert_int_eq(is_valid_expression("a+b^c"), true);
    ck_assert_int_eq(is_valid_expression("(a+b)"), true);
    ck_assert_int_eq(is_valid_expression("(a+b)-c"), true);
    ck_assert_int_eq(is_valid_expression("l/m^n*o-p"), true);
    ck_assert_int_eq(is_valid_expression("ag+ba-c+cedf^*+^*"), true);
    
} END_TEST

START_TEST(test_is_valid_expression_various_false){
    ck_assert_int_eq(is_valid_expression("(a+b"), false);
    ck_assert_int_eq(is_valid_expression("a+b^"), false);

    // This is taken as false beacuse the expression is empty
    ck_assert_int_eq(is_valid_expression("()"), false);
    
} END_TEST

/* Note that the following are invalid in both infix and rpn notation
 * but this is okay, since the is_valid_expression function is more of a 
 * sanity check/first pass than a robust syntax checker - syntax checkers
 * for each form of notation come about naturally in the parsing phase
 */

START_TEST(test_is_valid_expression_weird_cases){
    ck_assert_int_eq(is_valid_expression("a+bc^"), true);
    
    // again, false because it's empty, not beacuse of the syntax itself
    ck_assert_int_eq(is_valid_expression(")("), false);
    
} END_TEST


Suite * make_is_valid_expression_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_valid_expression");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_valid_expression_a);
    tcase_add_test(tc_core, test_is_valid_expression_A);
    tcase_add_test(tc_core, test_is_valid_expression_aplusb);
    tcase_add_test(tc_core, test_is_valid_expression_ab);
    tcase_add_test(tc_core, test_is_valid_expression_negb);
    tcase_add_test(tc_core, test_is_valid_expression_complex);
    tcase_add_test(tc_core, test_is_valid_expression_various_false);
    tcase_add_test(tc_core, test_is_valid_expression_weird_cases);
    suite_add_tcase(s, tc_core);

    return s;
}
