#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "rpn_utilities.h"

START_TEST(test_identify_type){
    ck_assert_int_eq(identify_type('a'), 1);
    ck_assert_int_eq(identify_type('b'), 1);
} END_TEST

Suite * utility_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("identify_type");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_identify_type);
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
