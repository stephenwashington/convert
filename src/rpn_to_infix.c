#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rpn_utilities.h"
#include "rpn_to_infix.h"


int16_t pop(uint8_t char_slice[1000], uint8_t expr[1000]){
    int16_t expr_length = 0;
    //printf("Attempting to pop %u - SIZES: %lu %lu \n",char_slice[0], strlen((char*)char_slice), strlen((char*)expr));
    memcpy(expr, char_slice, strlen((char*)char_slice));
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
        //printf("INSERTING %c at %d %d\n",command,(*len),0);
        stack[*len][0] = command;    
        (*len)++;
    } else if (is_valid_operator(command)){
        //printf("EXECUTING OPERATION: %c\n",command);
        if ((*len) < 2){
            fprintf(stderr, \
                  "Not enough expressions to perform operation: %c\n", command);
            exit(EXIT_FAILURE);
        }
        uint8_t expr_left[1000] = {0};
        uint8_t expr_right[1000] = {0};
        int16_t expr_right_len = pop(stack[(*len) - 1], expr_right);
        int16_t expr_left_len = pop(stack[(*len) - 2], expr_left);
        
        /* printf("LEFT: ");
        for (int16_t j = 0; j < 1000; j++){
            if (expr_left[j] != 0) printf("%c",expr_left[j]);
        }
        
        printf("\nRIGHT: ");
        for (int16_t j = 0; j < 1000; j++){
            if (expr_right[j] != 0) printf("%c",expr_right[j]);
        }*/
        
        uint8_t new_expr[1000] = {0};
        uint8_t left_paren = '(';
        uint8_t right_paren = ')';
        
        memcpy(new_expr, &left_paren, 1);
        memcpy(&new_expr[1], expr_left, expr_left_len);
        memcpy(&new_expr[expr_left_len+1], &command, 1);
        memcpy(&new_expr[expr_left_len+2], expr_right, expr_right_len);
        memcpy(&new_expr[expr_left_len+expr_right_len+2], &right_paren, 1);
        (*len) -= 2;
        memcpy(stack[*len], new_expr, 1000);
        /*printf("\nRESULT: ");
        for (int16_t j = 0; j < 1000; j++){
            if (stack[(*len)][j] != 0) printf("%c",stack[(*len)][j]);
        }
        printf("\n\n");*/  
        (*len)++;
    }
}
