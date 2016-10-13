#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "rpn_utilities.h"
#include "infix_to_rpn.h"

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command){
    //printf("%d %d %c\n", variable->length, symbol->length, command);
    if (is_variable(command)){
        memcpy(&variable->content[variable->length], &command, 1);
        variable->length++;
    } else if (is_symbol(command)){
        if (command == ')'){
            while (true){
                uint8_t c = symbol->content[symbol->length - 1];
                if(is_valid_operator(c)){
                    variable->content[variable->length] = c;
                    variable->length++;
                    symbol->content[symbol->length] = '0';
                    symbol->length--;
                } else if (is_parenthesis(c)){
                    symbol->content[symbol->length] = '0';
                    symbol->length--;
                    if (c == '(') break;
                }
            }
        } else {
            memcpy(&symbol->content[symbol->length], &command, 1);
            symbol->length++;
        }
    }
}
