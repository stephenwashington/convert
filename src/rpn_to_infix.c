#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rpn_utilities.h"
#include "rpn_to_infix.h"

// if command is a variable, append it to the end of the stack    
// if command is an operator
    // 1. pop off the two items at the right end of the stack
    // 2. Insert the operator between them
    // 3. Append the result, wrapped in parentheses, to the stack
// Otherwise, complain that we got a bad character and exit

void update_rpn_stack(uint8_t stack[][1000], int16_t *len, uint8_t command){
    if (is_variable(command)){
        stack[*len][0] = command;    
        (*len)++;
    } else if (is_valid_operator(command)){
        uint8_t *expr_right = stack[(*len) - 1];
        uint8_t *expr_left = stack[(*len) - 2];
        uint8_t new_expr[101];
        uint8_t left_paren = '(';
        uint8_t right_paren = ')';
        
        memcpy(new_expr, &left_paren, 1);
        memcpy(&new_expr[1], expr_left, 1);
        memcpy(&new_expr[2], &command, 1);
        memcpy(&new_expr[3], expr_right, 1);
        memcpy(&new_expr[4], &right_paren, 1);
        (*len) -= 2;
        memcpy(stack[*len], new_expr, 101);
    }
}
