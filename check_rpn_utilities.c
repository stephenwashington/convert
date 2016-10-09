#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "rpn_utilities.h"

START_TEST(test_identify_type_a){
    ck_assert_int_eq(identify_type('a'), 1);
} END_TEST

START_TEST (test_identify_type_b){
    ck_assert_int_eq(identify_type('b'), 1);
} END_TEST

START_TEST (test_identify_type_A){
    ck_assert_int_eq(identify_type('A'), -1);
} END_TEST

START_TEST (test_identify_special_char){
    ck_assert_int_eq(identify_type('/'), 1);
} END_TEST

Suite * utility_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("identify_type");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_identify_type_a);
    tcase_add_test(tc_core, test_identify_type_b);
    tcase_add_test(tc_core, test_identify_type_A);
    tcase_add_test(tc_core, test_identify_special_char);
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
