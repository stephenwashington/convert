#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "rpn_utilities.h"
#include "infix_to_rpn.h"

void update_infix_stacks(struct stack s, uint8_t command){
    memcpy(s.content, &command, 1);
}
