#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "utilities.h"
#include "unit_tests.h"
#include "infix_to_rpn.h"

START_TEST(test_infix_to_rpn_simple){
    char *result = infix_to_rpn("a");
    ck_assert_str_eq(result, "a");
    free(result);
} END_TEST

START_TEST(test_infix_to_rpn_ab){
    infix_to_rpn("ab");
} END_TEST

START_TEST(test_infix_to_rpn_a_plus_b){
    char *result = infix_to_rpn("a+b");
    ck_assert_str_eq(result, "ab+");
    free(result);
} END_TEST

START_TEST(test_infix_to_rpn_a_plus_b_minus_c){
    char *result = infix_to_rpn("a+b-c");
    ck_assert_str_eq(result, "abc-+");
    free(result);
} END_TEST

START_TEST(test_infix_to_rpn_obey_order_of_operations){
    char *result = infix_to_rpn("l/m^n*o-p");
    ck_assert_str_eq(result, "lmn^/o*p-");
    free(result);
} END_TEST

START_TEST(test_infix_to_rpn_expr_with_parentheses){
    char *result = infix_to_rpn("((v/w)^x)*(y-z)");
    ck_assert_str_eq(result, "vw/x^yz-*");
    free(result);
} END_TEST

START_TEST(test_infix_to_rpn_complex_expression){
    ck_assert_str_eq(infix_to_rpn("(a+g)*(((b-a)+c)^(c+(e*(d^f))))"),\
                                   "ag+ba-c+cedf^*+^*"); 
} END_TEST

START_TEST(test_infix_to_rpn_mismatched_parentheses){
    infix_to_rpn("(a+g)*(((b-a)+c)^(c+(e*(d^f))())");
} END_TEST

START_TEST(test_infix_to_rpn_mismatched_parentheses2){
    infix_to_rpn("(a+g)*((((b-a)+c)^(c+(e*(d^f))))");
} END_TEST

START_TEST(test_infix_to_rpn_mismatched_parentheses3){
    infix_to_rpn("(a)+g)*(((b-a)+c)^(c+(e*(d^f))))");
} END_TEST

START_TEST(test_infix_to_rpn_very_long_input){
    infix_to_rpn("(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)*(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z)");
} END_TEST

START_TEST(test_infix_to_rpn_rpn_input){
    infix_to_rpn("ab+c+d+");
} END_TEST

START_TEST(test_infix_to_rpn_bad_parentheses){
    infix_to_rpn("(a+)b");
} END_TEST

START_TEST(test_infix_to_rpn_valid_parentheses){
    char *result = infix_to_rpn("(a)");
    ck_assert_str_eq(result, "a");
    free(result);
} END_TEST

Suite * make_infix_to_rpn_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("infix_to_rpn");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_infix_to_rpn_simple);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_ab,\
                        EXIT_FAILURE);
    tcase_add_test(tc_core, test_infix_to_rpn_a_plus_b);
    tcase_add_test(tc_core, test_infix_to_rpn_a_plus_b_minus_c);
    tcase_add_test(tc_core,\
                   test_infix_to_rpn_obey_order_of_operations);
    tcase_add_test(tc_core, test_infix_to_rpn_expr_with_parentheses);
    tcase_add_test(tc_core, test_infix_to_rpn_complex_expression);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_mismatched_parentheses,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_mismatched_parentheses2,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_mismatched_parentheses3,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_very_long_input,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_rpn_input, EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_infix_to_rpn_bad_parentheses,\
                        EXIT_FAILURE);
    tcase_add_test(tc_core, test_infix_to_rpn_valid_parentheses);
    suite_add_tcase(s, tc_core);

    return s;
}
