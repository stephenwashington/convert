#include <stdint.h>
#include <stdbool.h>
#pragma once


// Our stack datatype - holds individual characters in an array
#define MAX_STACK_LENGTH 1000

struct stack{
    uint8_t content[MAX_STACK_LENGTH];
    int16_t length;
};

// Helper function to print an error and exit the program
void print_error(const char * msg);

// Helper functions to remove and add items to the stack
void append(struct stack *s, uint8_t c);
void pop(struct stack *s);

// Helper functions to identify individual characters
int16_t operator_precedence(uint8_t c);
bool is_operator(uint8_t c);
bool is_right_associative(uint8_t c);
bool is_parenthesis(uint8_t c);
bool is_variable(uint8_t c);
bool is_symbol(uint8_t c);
bool is_valid_char(uint8_t c);
