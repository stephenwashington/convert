#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rpn_utilities.h"
#include "rpn_to_infix.h"
#include "infix_to_rpn.h"

int main(void){
    char expr[500];
    printf("\n========== RPN To Infix Converter ==========\n\n");
    printf("Please input your expression to convert: ");
    
    if (fgets(expr, 500, stdin) == NULL){
        fprintf(stderr, "Couldn't get expression");
        exit(EXIT_FAILURE);
    }
    expr[strlen(expr) - 1] = '\0';
    
    printf("[1]: Convert from Reverse Polish Notation to Infix Notation\n");
    printf("[2]: Convert from Infix Notation to Reverse Polish Notation\n\n");
    printf("Your selection: ");
    
    uint8_t option = getchar();
    
    printf("\n");
    
    if (option == '1'){
        printf("RPN: %s\n",expr);
        printf("Infix: %s\n",rpn_to_infix(expr));
    } else if (option == '2'){
        printf("Infix: %s\n",expr);
        printf("RPN: %s\n",infix_to_rpn(expr));
    }
    printf("\n");
}
