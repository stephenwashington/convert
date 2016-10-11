#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "rpn_to_infix.h"

START_TEST(test_update_rpn_stack_simple){
    uint8_t *stack = NULL;
    uint8_t command = 'a';
    stack = update_rpn_stack(stack, sizeof(stack), command);
    ck_assert_int_eq(stack[0], 'a');

} END_TEST


Suite * make_update_rpn_stack_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("update_rpn_stack");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_update_rpn_stack_simple);
    suite_add_tcase(s, tc_core);

    return s;
}
