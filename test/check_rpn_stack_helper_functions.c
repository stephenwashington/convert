#include <stdint.h>
#include <check.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"

START_TEST(test_rpn_stack_helper_functions_add_single){
    struct stack s = { .content = {0}, .length = 0};
    append(&s, 'a');
    ck_assert_int_eq(s.content[0], 'a');
    ck_assert_int_eq(s.length, 1);
} END_TEST

START_TEST(test_rpn_stack_helper_functions_add_multiple){
    struct stack s = { .content = {0}, .length = 0};
    const char * input = "ab";
    for (uint16_t i = 0; i < strlen(input); i++){
        append(&s, input[i]);
    }
    ck_assert_int_eq(s.content[0], 'a');
    ck_assert_int_eq(s.content[1], 'b');
    ck_assert_int_eq(s.length, 2);
} END_TEST


Suite * make_rpn_stack_helper_functions_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("rpn_stack_helper_functions");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_rpn_stack_helper_functions_add_single);
    tcase_add_test(tc_core, test_rpn_stack_helper_functions_add_multiple);
    suite_add_tcase(s, tc_core);

    return s;
}
