#include <stdint.h>
#include <stdlib.h>
#include "utilities.h"
#pragma once

// Helper function that returns whether expr is a roughly valid RPN expression
bool is_valid_rpn_expr(const char *expr);

// Helper function that combines two expressions with an operator and wraps it
// in parentheses
char * combine_expr(char *expr_left, char *expr_right, uint8_t command);

// Updates the rpn stack array based on what command is
void update_rpn_stack(struct stack sarr[50], int16_t *location, uint8_t command);

// Covnert expr from RPN to infix
char * rpn_to_infix(const char * expr);
