#include <stdint.h>
#include <stdlib.h>
#include "utilities.h"
#pragma once

// Helper function for update_infix_stats (see src/infix_to_rpn.c)
bool should_pop(uint8_t command, uint8_t prev_command);

// Returns true if expr is a roughly valid infix expression
bool is_valid_infix_expr(const char *expr);

// Updatest the variable and symbol stacks according to command
void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command);
                            
// Covnerts expr from infix to RPN
char * infix_to_rpn(const char * expr);

