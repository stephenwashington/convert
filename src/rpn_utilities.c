#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

bool is_valid_operator(uint8_t c){
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^');
}

bool is_parenthesis(uint8_t c){
    return (c == '(') || (c == ')');
}

bool is_variable(uint8_t c){
    return isalpha(c) && islower(c);
}

bool is_valid_char(uint8_t c){
    return is_variable(c) || is_parenthesis(c) || is_valid_operator(c);
}

bool is_valid_expression(uint8_t *exp, size_t len){
    int16_t variable_count = 0;
    int16_t symbol_count = 0;
    for (uint16_t i = 0; i < len; i++){
        if (!is_valid_char(exp[i])){
            return false;
        }
        
        if (is_variable(exp[i])){
            variable_count++;
        } else if (is_valid_operator(exp[i]) || is_parenthesis(exp[i])){
            symbol_count++;
        }
    }
    return variable_count - 1 == symbol_count;
}
