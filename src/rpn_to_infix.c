#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
        uint8_t expr_right = stack[(*len) - 1][0];
        uint8_t expr_left = stack[(*len) - 2][0];
        (*len) -= 2;
        stack[*len][0] = expr_left;
        stack[*len][1] = command;
        stack[*len][2] = expr_right;
    }

}
