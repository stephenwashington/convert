#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rpn_utilities.h"
#include "rpn_to_infix.h"


int16_t pop(uint8_t char_slice[1000], uint8_t expr[1000]){
    int16_t expr_length = 0;
    //printf("Attempting to pop %u to %u\n",char_slice[0], expr[0]);
    memcpy(expr, char_slice, 1000);
    for (int16_t i = 0; i < 1000; i++){
        if (char_slice[i] == 0){
            break;
        }
        expr_length++;
        char_slice[i] = 0;
    }
    
    return expr_length;
}

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
        uint8_t expr_left[1000], expr_right[1000];
        int16_t expr_right_len = pop(stack[(*len) - 1], expr_right);
        int16_t expr_left_len = pop(stack[(*len) - 2], expr_left);
        //printf("Pop stats: %d %d\n",expr_left_len, expr_right_len);
        
        uint8_t new_expr[1000];
        uint8_t left_paren = '(';
        uint8_t right_paren = ')';
        
        memcpy(new_expr, &left_paren, 1);
        memcpy(&new_expr[1], expr_left, expr_left_len);
        memcpy(&new_expr[expr_left_len+1], &command, 1);
        memcpy(&new_expr[expr_left_len+2], expr_right, expr_right_len);
        memcpy(&new_expr[expr_left_len+expr_right_len+2], &right_paren, 1);
        (*len) -= 2;
        memcpy(stack[*len], new_expr, 1000);
    }
}
