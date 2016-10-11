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
    return (isalpha(c) && islower(c)) || \
            is_parenthesis(c) || is_valid_operator(c);
}

bool is_valid_expression(uint8_t *exp){
    int16_t length = sizeof(exp) / 8; //sizeof(unsigned char) always returns 1
    for (int16_t i = 0; i < length; i++){
        if (!is_valid_char(exp[i])){
            return false;
        }
    }
    return true;
}
