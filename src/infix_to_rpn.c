#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "rpn_utilities.h"
#include "infix_to_rpn.h"

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command){
                            
    if (is_variable(command)){
        memcpy(&variable->content[variable->length], &command, 1);
        variable->length++;
    } else if (is_symbol(command)){
        memcpy(&symbol->content[symbol->length], &command, 1);
        symbol->length++;
    }
}
