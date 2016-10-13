#include <stdint.h>
#include <check.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "rpn_unit_tests.h"
#include "infix_to_rpn.h"

START_TEST(test_update_infix_stacks_simple){
    uint8_t variable_stack[1000] = {0};
    const char input[] = "a";
    for (uint16_t i = 0; i < strlen(input); i++){
        update_infix_stacks(variable_stack, input[i]);
    }
    
    ck_assert_str_eq((char*)variable_stack, "a");
} END_TEST

Suite * make_update_infix_stacks_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("update_infix_stacks");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_update_infix_stacks_simple);

    return s;
}
