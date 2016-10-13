#include <stdint.h>
#include <stdlib.h>

struct stack{
    uint8_t content[1000];
    int16_t length;
};

void update_infix_stacks(struct stack s, uint8_t command);
