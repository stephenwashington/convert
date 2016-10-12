#include <stdint.h>
#include <stdlib.h>

void update_rpn_stack(uint8_t stack[][1000], int16_t *len, uint8_t command);
const char * rpn_to_infix(const char * expr);
