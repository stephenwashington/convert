#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include "unit_tests.h"

int main(void){
    int16_t number_failed;
    SRunner *sr;

    sr = srunner_create(make_rpn_utilities_suite());
    srunner_add_suite(sr, make_rpn_to_infix_suite());
    srunner_add_suite(sr, make_infix_to_rpn_suite());
    srunner_add_suite(sr, make_rpn_stack_helper_suite());
    
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
