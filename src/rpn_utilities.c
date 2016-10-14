#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

bool is_valid_operator(uint8_t c){
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^');
}

int16_t operator_precedence(uint8_t c){
    if (c == '+') return 5; 
    if (c == '-') return 4; 
    if (c == '*') return 3; 
    if (c == '/') return 2;
    if (c == '^') return 1;
    return 0;
}

bool is_right_associative(uint8_t c){
    return (c == '^');
}

bool is_parenthesis(uint8_t c){
    return (c == '(') || (c == ')');
}

bool is_variable(uint8_t c){
    return isalpha(c) && islower(c);
}

bool is_symbol(uint8_t c){
    return is_valid_operator(c) || is_parenthesis(c);
}

bool is_valid_char(uint8_t c){
    return is_variable(c) || is_symbol(c);
}

bool is_valid_expression(const char *exp){
    int16_t variable_count = 0;
    int16_t operator_count = 0;
    int16_t paren_count = 0;
    for (uint16_t i = 0; i < strlen(exp); i++){
        if (!is_valid_char(exp[i])){
            return false;
        }
        
        if (is_variable(exp[i])){
            variable_count++;
        } else if (is_valid_operator(exp[i])){
            operator_count++;
        } else {
            paren_count++;
        }
    }
    return (variable_count - 1 == operator_count) && (paren_count % 2 == 0);
}
