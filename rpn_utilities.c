#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "rpn_utilities.h"

int16_t identify_type(uint8_t c){
    if (isalpha(c) && islower(c)){
        return 1;
    }
    return -1;
}
