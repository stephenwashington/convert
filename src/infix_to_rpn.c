#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"
#include "infix_to_rpn.h"

/* Given the current and previously added operator to the operator stack,
 * determine whether or not we need to pop off the previous operator
 *
 * Conditions for this being true:
 *     1. The current operator is right-associative (i.e. '^') AND has a higher
 *        precedence than the previous operator
 *     OR
 *     2. The current operator is left-associative (i.e. '^') AND has a higher 
 *        or equal precedence than the previous operator
 *
 */

bool should_pop(uint8_t command, uint8_t prev_command){
    bool a = is_right_associative(command);
    bool b = operator_precedence(prev_command) < operator_precedence(command);
    bool c = !is_right_associative(command);
    bool d = operator_precedence(prev_command) <= operator_precedence(command);
    return (a && b) || (c && d);
}

/* Helper function that returns whether expr is a valid infix expression
 * 
 * An infix expression is valid if the number of variables (letters) is one more
 * than the number of operators ( / + - * ^ ), and the parentheses match up
 * (i.e. there are an equal number of '(' and ')'). In addition, the expression
 * is valid iff each expression contained within () is also valid using the
 * conditions above
 * 
 * Note that this function does not catch all instances of syntactically invalid
 * expressions - those cases that fool this function tend to be caught when the
 * expression is converted
 */

bool is_valid_infix_expr(const char *expr){
    int16_t variable_count = 0;
    int16_t operator_count = 0;
    int16_t left_paren_count = 0;
    int16_t right_paren_count = 0;
    for (uint16_t i = 0; i < strlen(expr); i++){
    
        // Handle cases like "ab+c"
        if (i > 0 && i < strlen(expr) - 1){
            if (is_variable(expr[i]) && \
               (is_variable(expr[i-1]) || is_variable(expr[i+1]))){
                return false;
            }
        }
        if (is_variable(expr[i])){
            variable_count++;
        } else if (is_operator(expr[i])){
            operator_count++;
        } else if (expr[i] == '(') {
            left_paren_count++;
        } else if (expr[i] == ')') {
            right_paren_count++;
        } else return false;
    }
    
    if ((variable_count - 1 != operator_count) || \
           (left_paren_count != right_paren_count)){
        return false;       
    }
    
    //handle cases like (a+)b
    int16_t begin = -1, end = -1;
    left_paren_count = 0;
    right_paren_count = 0;
    for (uint16_t i = 0; i < strlen(expr); i++){
        if (expr[i] == '('){
            if (begin == -1) begin = i;
            left_paren_count++;
        } else if (expr[i] == ')'){
            right_paren_count++;
            if (left_paren_count == right_paren_count){
                end = i;
                int16_t len = end - begin;
                char substr[len-2];
                memcpy(&substr, &expr[begin+1], len-1);
                substr[len-1] = '\0';
                if(!is_valid_infix_expr(substr)){
                    return false;
                } else {
                    begin = -1;
                    end = -1;
                }
            }
        }
    }
    
    return true;
    
}

/* Given a stack for variables, a stack for symbols (operators and parentheses),
 * and a command (either a variable or a symbol), execute that command
 *
 * - If command is a variable, just add it to the variable stack
 * - If command is a symbol:
 *     - If command is '(', add it to the symbol stack
 *     - If command is an operator and there is at least one symbol on the
 *       symbol stack:
 *         - Starting with the top item on the stack and working down, append
 *           all previous items to the stack that satisfy the conditions
 *           outlined in should_pop above. Break if we run out of operators or
 *           we reach a parenthesis
 *         - Append the command to the symbol stack when we finish (or simply
 *           append the operator if the symbol stack is empty)
 *     - If command is ')' then, starting with the top of the steak and working
 *       our way down, remove each item from the symbol stack and move it to the
 *       variable stack. Stop when we reach a '('
 *     - Otherwise, append the command to the symbol stack
 * - Otherwise, report that we encountered an invalid character and exit
 */

void update_infix_stacks(struct stack *variable, struct stack *symbol,\
                            uint8_t command){
    if (is_variable(command)){
        append(variable, command);
    }
    else if (is_symbol(command)){
        if (command == ')'){
            uint8_t c = symbol->content[symbol->length - 1];
            while (c != '('){
                if (symbol->length == 0){
                    print_error("Mismatched parentheses");
                }
                c = symbol->content[symbol->length - 1];
                if(is_operator(c)){
                    append(variable, c);
                    pop(symbol);
                }
            }
            pop(symbol);
            
        } else if (is_operator(command) && symbol->length > 0) {
            uint8_t prev_operator = symbol->content[symbol->length - 1];
            while (symbol->length > 0 && !is_parenthesis(prev_operator)){
                prev_operator = symbol->content[symbol->length - 1];
                if (should_pop(command, prev_operator)){
                    append(variable, prev_operator);
                    pop(symbol);
                } else break;
            }
            append(symbol, command);
            
        } else append(symbol, command);
    } else {
        print_error("Invalid character detected");
    }
}

/* Given an infix expression, return the equivalent RPN expression
 * 1. Create and initialize two stacks: one for variables, one for symbols
 * 2. Loop through the infix expression, executing each character in it as a
 *    command (see update_infix_stacks for the specifics)
 * 3. Once we're done, append any remaning characters on the symbol stack to the
 *    variable stack
 * 4. The contents of the variable stack will contain the final expression
 *
 * This function will throw a fatal error if:
 *     - The initial infix expression is invalid (see is_valid_infix_expr)
 *     - The final RPN expression contains a parenthesis (usually the result of
 *       mis-matched parentheses)
 */

char * infix_to_rpn(const char * expr){
    struct stack variable_stack = { .content = {0}, .length = 0};
    struct stack symbol_stack = { .content = {0}, .length = 0};
    
    if (!is_valid_infix_expr(expr)){
        print_error("Invalid infix expression");
    }
    
    for (uint16_t i = 0; i < strlen(expr); i++){
        update_infix_stacks(&variable_stack, &symbol_stack, expr[i]);
    }
    
    for (int16_t i = symbol_stack.length-1; i >= 0; i--){
        variable_stack.content[variable_stack.length] = symbol_stack.content[i];
        variable_stack.length++;
    }
    
    for (int16_t i = 0; i < variable_stack.length; i++){
        if (is_parenthesis(variable_stack.content[i])){
            print_error("Mismatched parentheses in expression");
        }
    }
    char *result = calloc(1000, sizeof(char));
    memcpy(result, variable_stack.content, 1000);
    return result;
}
