#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "rpn_utilities.h"

const uint8_t valid_symbols[7] = {'(', ')', '^', '/', '*', '-', '+'};

int16_t identify_type(uint8_t c){
    if (isalpha(c) && islower(c)){
        return 1;
    } else{
        for (int16_t i = 0; i < 7; i++){
            if (c == valid_symbols[i]){
                return 1;
            }
        }
    }
    return -1;
}
