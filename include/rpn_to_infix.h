#include <stdint.h>
#include <stdlib.h>
#include "rpn_utilities.h"
#pragma once

bool is_valid_rpn_expr(const char *expr);
char * combine_expr(char *expr_left, char *expr_right, uint8_t command);
void update_rpn_stack(struct stack sarr[50], int16_t *location, uint8_t command);
const char * rpn_to_infix(const char * expr);
