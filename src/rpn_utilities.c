#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

const uint8_t valid_symbols[7] = {'(', ')', '^', '/', '*', '-', '+'};

bool is_parenthesis(uint8_t c){
    return (c == '(') || (c == ')');
}

bool is_valid_char(uint8_t c){
    if (isalpha(c) && islower(c)){
        return true;
    } else{
        for (int16_t i = 0; i < 7; i++){
            if (c == valid_symbols[i]){
                return true;
            }
        }
    }
    return false;
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
