#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include "rpn_unit_tests.h"

int main(void){
    int16_t number_failed;
    SRunner *sr;

    sr = srunner_create(make_is_valid_char_suite());
    srunner_add_suite(sr, make_is_valid_expression_suite());
    srunner_add_suite(sr, make_is_parenthesis_suite());
    srunner_add_suite(sr, make_is_valid_operator_suite());
    

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
