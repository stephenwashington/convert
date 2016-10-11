#include <stdint.h>
#include <stdlib.h>
#include "rpn_utilities.h"
#include "rpn_to_infix.h"

// if command is a variable, append it to the end of the stack    
// if command is an operator
    // 1. pop off the two items at the right end of the stack
    // 2. Insert the operator between them
    // 3. Append the result, wrapped in parentheses, to the stack

uint8_t * update_rpn_stack(uint8_t *stack, size_t len, uint8_t command){
    uint8_t *newstack = (uint8_t *)realloc(stack, (len+1)*sizeof(uint8_t));
    newstack[0] = command;
    return newstack;
}
