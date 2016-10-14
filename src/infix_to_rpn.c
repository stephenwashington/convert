#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "infix_to_rpn.h"

bool should_pop(uint8_t command, uint8_t prev_command){
    bool a = is_right_associative(command);
    bool b = operator_precedence(prev_command) < operator_precedence(command);
    bool c = !is_right_associative(command);
    bool d = operator_precedence(prev_command) <= operator_precedence(command);
    return (a && b) || (c && d);
}

bool is_valid_infix_expr(const char *expr){
    int16_t variable_count = 0;
    int16_t operator_count = 0;
    int16_t left_paren_count = 0;
    int16_t right_paren_count = 0;
    for (uint16_t i = 0; i < strlen(expr); i++){
        if (is_variable(expr[i])){
            variable_count++;
        } else if (is_valid_operator(expr[i])){
            operator_count++;
        } else if (expr[i] == '(') {
            left_paren_count++;
        } else if (expr[i] == ')') {
            right_paren_count++;
        } else return false;
    }
    
    return (variable_count - 1 == operator_count) && \
           ((left_paren_count + right_paren_count) % 2 == 0) && \
           (left_paren_count == right_paren_count);
}

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command){
    if (is_variable(command)){
        append(variable, command);
    }
    else if (is_symbol(command)){
        if (command == ')'){
            uint8_t c = symbol->content[symbol->length - 1];
            while (symbol->length > 0 && is_valid_operator(c)){
                c = symbol->content[symbol->length - 1];
                if(is_valid_operator(c)){
                    append(variable, c);
                    pop(symbol);
                }
                else if (is_parenthesis(c)){
                    pop(symbol);
                    if (c == '(') break;
                }
            }
            
        } else if (is_valid_operator(command) && symbol->content[symbol->length - 1]) {
            uint8_t prev_operator = symbol->content[symbol->length - 1];
            while (symbol->length > 0 && !is_parenthesis(prev_operator)){
                prev_operator = symbol->content[symbol->length - 1];
                if (should_pop(command, prev_operator)){
                    append(variable, prev_operator);
                    pop(symbol);
                } else break;
            }
            append(symbol, command);
            
        } else append(symbol, command);
    }
}

const char * infix_to_rpn(const char * expr){
    struct stack variable_stack = { .content = {0}, .length = 0};
    struct stack symbol_stack = { .content = {0}, .length = 0};
    
    if (!is_valid_infix_expr(expr)){
        //fprintf(stderr, "Invalid expression\n");
        exit(EXIT_FAILURE);
    }
    
    for (uint16_t i = 0; i < strlen(expr); i++){
        update_infix_stacks(&variable_stack, &symbol_stack, expr[i]);
    }
    
    for (int16_t i = symbol_stack.length-1; i >= 0; i--){
        variable_stack.content[variable_stack.length] = symbol_stack.content[i];
        variable_stack.length++;
    }
    
    for (int16_t i = 0; i < variable_stack.length; i++){
        if (is_parenthesis(variable_stack.content[i])){
            //fprintf(stderr, "Mismatched parentheses in expression\n");
            exit(EXIT_FAILURE);
        }
    }
    char *result = calloc(1000, sizeof(char));
    memcpy(result, variable_stack.content, 1000);
    return result;
}
