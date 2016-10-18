#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "utilities.h"

/* Helper function to report errors to the user
 */
 
void print_error(const char * msg){
    fprintf(stderr, "ERROR: %s\n",msg);
    exit(EXIT_FAILURE);
}

/* Helper functions to append and remove items from the stack
 * MAX_STACK_LENGTH is 1000 by default, so we can protect ourselves from stack
 * overflow issues
 */

void append(struct stack *s, uint8_t c){
    if (s->length == MAX_STACK_LENGTH){
        print_error("Stack overflow");
    }
    if (!is_valid_char(c)){
        print_error("Invalid character detected");
    }
    memcpy(&s->content[s->length], &c, 1);
    s->length++;
}

void pop(struct stack *s){
    if (s->length == 0){
        print_error("Attempting to pop off of empty stack");
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
