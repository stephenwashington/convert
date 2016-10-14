#include <stdint.h>
#include <stdlib.h>
#pragma once

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command);
bool should_pop(uint8_t command, uint8_t prev_command);
const char * infix_to_rpn(const char * expr);
bool is_valid_infix_expr(const char *expr);
