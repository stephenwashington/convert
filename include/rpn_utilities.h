#include <stdint.h>
#include <stdbool.h>
#pragma once

#define MAX_STACK_LENGTH 1000

struct stack{
    uint8_t content[MAX_STACK_LENGTH];
    int16_t length;
};

void append(struct stack *s, uint8_t c);
void pop(struct stack *s);

int16_t operator_precedence(uint8_t c);
bool is_operator(uint8_t c);
bool is_right_associative(uint8_t c);
bool is_parenthesis(uint8_t c);
bool is_variable(uint8_t c);
bool is_symbol(uint8_t c);
bool is_valid_char(uint8_t c);
