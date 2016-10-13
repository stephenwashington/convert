#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "rpn_utilities.h"
#include "infix_to_rpn.h"

void update_infix_stacks(uint8_t variable_stack[1000], uint8_t command){

    memcpy(variable_stack, &command, 1);
    return;
                        
}
