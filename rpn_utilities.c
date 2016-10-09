#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "rpn_utilities.h"

int8_t identify_type(char *c){
    if (strcmp(c, "a") == 0){
        return 1;
    }
    return -1;
}
