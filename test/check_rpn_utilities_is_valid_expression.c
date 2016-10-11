#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_is_valid_expression_a){
    uint8_t exp[1] = {'a'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), true);
} END_TEST

START_TEST(test_is_valid_expression_A){
    uint8_t exp[1] = {'A'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), false);
} END_TEST

START_TEST(test_is_valid_expression_aplusb){
    uint8_t exp[3] = {'a', '+', 'b'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), true);
} END_TEST

START_TEST(test_is_valid_expression_ab){
    uint8_t exp[2] = {'a', 'b'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), false);
} END_TEST

START_TEST(test_is_valid_expression_negb){
    uint8_t exp[2] = {'-', 'b'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), false);
} END_TEST

START_TEST(test_is_valid_expression_aplusb_inparen){
    uint8_t exp[5] = {'(', 'a', '+', 'b', ')'};
    ck_assert_int_eq(is_valid_expression(exp, sizeof(exp)), true);
} END_TEST

START_TEST(test_is_valid_expression_various_false){
    uint8_t exp1[4] = {'(', 'a', '+', 'b'};
    ck_assert_int_eq(is_valid_expression(exp1, sizeof(exp1)), false);
    
    uint8_t exp2[4] = {'a', '+', 'b', '^'};
    ck_assert_int_eq(is_valid_expression(exp2, sizeof(exp2)), false);
    
    // This is taken as false beacuse the expression is empty
    uint8_t exp3[2] = {'(', ')'};
    ck_assert_int_eq(is_valid_expression(exp3, sizeof(exp3)), false);
} END_TEST

START_TEST(test_is_valid_expression_various_true){
    uint8_t exp1[5] = {'a', '+', 'b', '^', 'c'};
    ck_assert_int_eq(is_valid_expression(exp1, sizeof(exp1)), true);
    
/* Note that the following are invalid in both infix and rpn notation
 * but this is okay, since the is_valid_expression function is more of a 
 * sanity check/first pass than a robust syntax checker - syntax checkers
 * for each form of notation come about naturally in the parsing phase
 */
    uint8_t exp2[5] = {'a', '+', 'b', 'c', '^'};
    ck_assert_int_eq(is_valid_expression(exp2, sizeof(exp2)), true);
    
    uint8_t exp3[2] = {')', '('};
    ck_assert_int_eq(is_valid_expression(exp3, sizeof(exp3)), false);
    
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
    tcase_add_test(tc_core, test_is_valid_expression_aplusb_inparen);
    tcase_add_test(tc_core, test_is_valid_expression_various_false);
    tcase_add_test(tc_core, test_is_valid_expression_various_true);
    suite_add_tcase(s, tc_core);

    return s;
}
