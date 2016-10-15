#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_rpn_stack_helper_functions_pop_single){
    struct stack s = { .content = {0}, .length = 0};
    append(&s, 'a');
    pop(&s);
    ck_assert_int_eq(s.content[0], '\0');
    ck_assert_int_eq(s.length, 0);
} END_TEST


Suite * make_rpn_stack_helper_functions_pop_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_stack_helper_functions_pop");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_stack_helper_functions_pop_single);
    suite_add_tcase(s, tc_core);

    return s;
}
