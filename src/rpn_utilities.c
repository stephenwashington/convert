#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

/* Helper functions to append and remove items from the stack
 * MAX_STACK_LENGTH is 1000 by default, so we can protect ourselves from stack
 * overflow issues
 */

void append(struct stack *s, uint8_t c){
    if (s->length == MAX_STACK_LENGTH){
        fprintf(stderr, "Stack overflow error\n");
        exit(EXIT_FAILURE);
    }
    if (!is_valid_char(c)){
        fprintf(stderr, "Cannot append this character: %c\n", c);
        exit(EXIT_FAILURE);
    }
    memcpy(&s->content[s->length], &c, 1);
    s->length++;
}

void pop(struct stack *s){
    if (s->length == 0){
        fprintf(stderr, "Attempting to pop off of empty stack\n");
        exit(EXIT_FAILURE);
    }
    s->content[s->length - 1] = '\0';
    s->length--;
}

/* Several helper functions that focus on character identification 
 *
 * The purpose of the names of the functions should be self-explanatory, given
 * their names
 */

// For this project, lower number indicates higher precedence
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

// See https://en.wikipedia.org/wiki/Operator_associativity
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
