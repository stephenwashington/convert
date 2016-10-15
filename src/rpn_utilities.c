#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

void append(struct stack *s, uint8_t c){
    memcpy(&s->content[s->length], &c, 1);
    s->length++;
}

void pop(struct stack *s){
    s->content[s->length] = '0';
    s->length--;
}

int16_t operator_precedence(uint8_t c){
    if (c == '+') return 5; 
    if (c == '-') return 4; 
    if (c == '*') return 3; 
    if (c == '/') return 2;
    if (c == '^') return 1;
    return 6;
}

bool is_operator(uint8_t c){
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^');
}

bool is_right_associative(uint8_t c){
    return (is_operator(c) && c == '^');
}

bool is_parenthesis(uint8_t c){
    return (c == '(') || (c == ')');
}

bool is_variable(uint8_t c){
    return isalpha(c) && islower(c);
}

bool is_symbol(uint8_t c){
    return is_operator(c) || is_parenthesis(c);
}

bool is_valid_char(uint8_t c){
    return is_variable(c) || is_symbol(c);
}
