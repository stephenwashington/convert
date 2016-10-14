#include <stdint.h>
#include <stdbool.h>
#pragma once

bool is_valid_char(uint8_t c);
bool is_valid_expression(const char *exp);
bool is_parenthesis(uint8_t c);
bool is_valid_operator(uint8_t c);
bool is_variable(uint8_t c);
bool is_symbol(uint8_t c);
int16_t operator_precedence(uint8_t c);
bool is_right_associative(uint8_t c);
