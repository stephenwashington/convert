#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "rpn_to_infix.h"

/* Helper function that returns whether expr is a valid RPN expression
 * 
 * An RPN expression is valid if the number of variables (letters) is one more
 * than the number of operators ( / + - * ^ )
 * 
 * Note that this function does not catch all instances of syntactically invalid
 * expressions - those cases that fool this function tend to be caught when the
 * expression is converted
 */

bool is_valid_rpn_expr(const char *expr){
    int16_t variable_count = 0;
    int16_t operator_count = 0;
    for (uint16_t i = 0; i < strlen(expr); i++){
        if (is_variable(expr[i])){
            variable_count++;
        } else if (is_operator(expr[i])){
            operator_count++;
        } else return false;
        
        if ((variable_count == operator_count) && variable_count > 0){
            return false;
        }
    }
    
    return (variable_count - 1 == operator_count);
}

/* Helper function that combines two expressions with an operator and wrapper 
 * parentheses (see the documentation for update_rpn_stack below)
 */

char * combine_expr(char *expr_left, char *expr_right, uint8_t command){
    char *expr = calloc(strlen(expr_left) + strlen(expr_right) + 4,\
                 sizeof(char));
    const char *left_paren = "(";
    const char *right_paren = ")";
    memcpy(expr, left_paren, 1);
    memcpy(&expr[1], expr_left, strlen(expr_left));
    memcpy(&expr[strlen(expr_left) + 1], &command, 1);
    memcpy(&expr[strlen(expr_left) + 2], expr_right, strlen(expr_right));
    memcpy(&expr[strlen(expr_left) + strlen(expr_right) + 2], right_paren, 1);
    return expr;
}

/*  Given a stack array, our position in the stack array, and a command, execute
*   the command
 *  - if command is a variable, append it to the end of the stack array and 
 *    increment location    
 *  - if command is an operator, call combine_expr, which will:
 *      1. pop off the two items at the right end of the stack
 *      2. Insert the operator between them
 *      3. Append the result, wrapped in parentheses, to the stack
      decrement location after this is done
 *
 *  - This function will throw an error and end the program if:
 *      - An attempt is made to combine to expressions when there is only one
 *        expression in the stack array
 *      - command is neither a variable or an operator 
 */
 
void update_rpn_stack(struct stack sarr[50], int16_t *location,uint8_t command){
    if (is_variable(command)){
        sarr[*location].content[0] = command;    
        (*location)++;
    } else if (is_operator(command)){
    
        if ((*location) < 2){
            print_error("Not enough expressions to perform all operations");
        }
        
        char *expr_left = (char*)sarr[(*location) - 2].content;
        char *expr_right = (char*)sarr[(*location) - 1].content;
        char *new_expr = combine_expr(expr_left, expr_right, command);
        
        sarr[(*location) - 1] = (struct stack){{0}, 0};
        sarr[(*location) - 2] = (struct stack){{0}, 0};
        
        (*location) -= 2;
        
        // Doing it this way (as opposed to memcpy) allows us to protect against
        // stack overflow issues
        for (uint16_t i = 0; i < strlen(new_expr); i++){
            append(&sarr[(*location)], new_expr[i]);
        }

        (*location)++;
        free(new_expr);
    } else {
        print_error("Invalid character detected");
    }
}

/* Given an expression expr in RPN, convert it to infix and return the result
 * 1. Create an array of 50 stacks. Each stack will contain one expression
 * 2. Loop through expr, executing each command on the stack array (see
 *    update_rpn_stack)
 * 3. Return the contents of the first stack in stack_arr - this will have the
 *    final expression, since all sub-expressions are combined into one final
 *    expression by the end (or should be, assuming good input)
 *
 * This function will throw an error and exit the program if:
 *     - The initial RPN expression is invalid
 *     - The final infix expression is invalid (this will be shown by there 
 *       being more than one expression remaining in the stack array, which can
 *       be caused by a deficit of operators (e.g. 'ab' will fail)
 */
char * rpn_to_infix(const char * expr){
    if (!is_valid_rpn_expr(expr)){
        print_error("Invalid RPN expression");
    }

    struct stack stack_arr[50];
    int16_t location = 0;
    for (int16_t i = 0; i < 50; i++){
        stack_arr[i] = (struct stack){{0}, 0};
    }
    
    for (uint16_t i = 0; i < strlen(expr); i++){
        update_rpn_stack(stack_arr, &location, expr[i]);
    }
    
    //Check to make sure we only have one expression remaining
    for (int16_t i = 1; i < 50; i++){
        if (stack_arr[i].content[0] != 0){
            print_error("Too many variables in expression");
        }
    }

    char *result = calloc(1000, sizeof(char));
    memcpy(result, stack_arr[0].content, 1000);
    return result;
}
