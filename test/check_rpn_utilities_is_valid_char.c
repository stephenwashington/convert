#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"

START_TEST(test_is_valid_char_a){
    ck_assert_int_eq(is_valid_char('a'), true);
} END_TEST

START_TEST (test_is_valid_char_b){
    ck_assert_int_eq(is_valid_char('b'), true);
} END_TEST

START_TEST (test_is_valid_char_A){
    ck_assert_int_eq(is_valid_char('A'), false);
} END_TEST

START_TEST (test_identify_valid_special_char){
    ck_assert_int_eq(is_valid_char('('), true);
    ck_assert_int_eq(is_valid_char(')'), true);
    ck_assert_int_eq(is_valid_char('^'), true);
    ck_assert_int_eq(is_valid_char('/'), true);
    ck_assert_int_eq(is_valid_char('*'), true);
    ck_assert_int_eq(is_valid_char('-'), true);
    ck_assert_int_eq(is_valid_char('+'), true);
} END_TEST

START_TEST (test_identify_invalid_special_char){
    ck_assert_int_eq(is_valid_char('{'), false);
    ck_assert_int_eq(is_valid_char('.'), false);
    ck_assert_int_eq(is_valid_char('%'), false);
} END_TEST

Suite * utility_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("is_valid_char");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_valid_char_a);
    tcase_add_test(tc_core, test_is_valid_char_b);
    tcase_add_test(tc_core, test_is_valid_char_A);
    tcase_add_test(tc_core, test_identify_valid_special_char);
    tcase_add_test(tc_core, test_identify_invalid_special_char);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = utility_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
