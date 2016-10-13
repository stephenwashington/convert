#include <stdint.h>
#include <stdlib.h>
#pragma once

struct stack{
    uint8_t content[1000];
    int16_t length;
};

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command);
bool should_pop_stack(uint8_t command, uint8_t prev_command);
void append(struct stack *s, uint8_t c);
void pop_stack(struct stack *s);
