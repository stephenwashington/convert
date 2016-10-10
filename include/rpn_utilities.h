#include <stdint.h>
#include <stdbool.h>
#pragma once

bool is_valid_char(uint8_t c);
bool is_valid_expression(uint8_t *exp);
bool is_parenthesis(uint8_t c);
bool is_valid_operator(uint8_t c);
bool is_variable(uint8_t c);
