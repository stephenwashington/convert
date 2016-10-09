#include <stdlib.h>
#include <check.h>
#include "rpn_utilities.h"

START_TEST(test_echo_int){
    ck_assert_int_eq(identify_type("a"), 1);
} END_TEST

Suite * echo_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("identify");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_echo_int);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = echo_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
