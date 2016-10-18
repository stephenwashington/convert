#include <check.h>
#include "utilities.h"
#include "unit_tests.h"
#include "rpn_to_infix.h"

START_TEST(test_rpn_to_infix_simple){
    char *result = rpn_to_infix("a");
    ck_assert_str_eq(result, "a");
    free(result);
} END_TEST

START_TEST(test_rpn_to_infix_a_plus_b){
    char *result = rpn_to_infix("ab+");
    ck_assert_str_eq(result, "(a+b)");
    free(result);
} END_TEST

START_TEST(test_rpn_to_infix_ab_throw_error){
    rpn_to_infix("ab");
} END_TEST

START_TEST(test_rpn_to_infix_medium_difficulty){
    char *result = rpn_to_infix("vw/x^yz-*");
    ck_assert_str_eq(result, "(((v/w)^x)*(y-z))");
    free(result);
} END_TEST

START_TEST(test_rpn_to_infix_hard_difficulty){
    char *result = rpn_to_infix("ag+ba-c+cedf^*+^*");
    ck_assert_str_eq(result, "((a+g)*(((b-a)+c)^(c+(e*(d^f)))))");
    free(result);
} END_TEST

START_TEST(test_rpn_to_infix_too_many_expressions){
    rpn_to_infix("ag+ba-c+cedf*");
} END_TEST

START_TEST(test_rpn_to_infix_too_long_input){
    rpn_to_infix("ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*ab+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+*");
} END_TEST

START_TEST(test_rpn_to_infix_infix_input){
    rpn_to_infix("a+b");
} END_TEST

Suite * make_rpn_to_infix_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_to_infix");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_to_infix_simple);
    tcase_add_test(tc_core, test_rpn_to_infix_a_plus_b);
    tcase_add_exit_test(tc_core, test_rpn_to_infix_ab_throw_error,EXIT_FAILURE);
    tcase_add_test(tc_core, test_rpn_to_infix_medium_difficulty);
    tcase_add_test(tc_core, test_rpn_to_infix_hard_difficulty);
    tcase_add_exit_test(tc_core, test_rpn_to_infix_too_many_expressions,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_rpn_to_infix_too_long_input,\
                        EXIT_FAILURE);
    tcase_add_exit_test(tc_core, test_rpn_to_infix_infix_input, EXIT_FAILURE);
    suite_add_tcase(s, tc_core);

    return s;
}
