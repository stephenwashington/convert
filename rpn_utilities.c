#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "rpn_utilities.h"

const uint8_t valid_symbols[7] = {'(', ')', '^', '/', '*', '-', '+'};

bool is_valid(uint8_t c){
    if (isalpha(c) && islower(c)){
        return true;
    } else{
        for (int16_t i = 0; i < 7; i++){
            if (c == valid_symbols[i]){
                return true;
            }
        }
    }
    return false;
}
