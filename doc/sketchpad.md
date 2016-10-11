#GENERAL STRUCTURE

File: utilities.c:
    + is_parenthesis: return true if character is "()"
    + is_valid_symbol: return true if character is in "^/*-+"
    + is_valid_char: return true if character is valid
        - Valid characters: lowercase english alphabet or is_valid_symbol() or is_parenthesis()
        
    + is_valid_expression: return true if all characters of a expression are roughly syntactically valid (either RPN or infix)
        - Test: Given n variables, there must be EXACTLY n-1 operators and the same number of '(' and ')' in the expression
        - This is only to be used as a rough check - more stringent checking (with throwable errors)
          will occur when the script attempts to convert the expression
        
File: rpn.c
    - rpn_update_stack: Given a pointer to a RPN stack and a command in the form of a single character, execute that command
        - If 'command' is a letter, add that letter to the top of the stack
        - If 'command' is a symbol:
            1. Pop off the top two entries in the stack
            2. Execute the operation (check if there are two operands first!)
            3. Wrap the result in parentheses
            4. Add the result back to the stack
        - return the stack
        
    - rpn_to_infix: given a RPN expression, return the equivalent infix expression
        - Determine if RPN expression if valid
        - Loop through expression, executing update_stack on each character
        - Once the loop is done, convert stack to expression (will be infix format)
        - return this expression
        
File: infix.c

    - infix_update_stacks: Given pointers to 'result' stack and 'symbols' and a command in the form of a single character, execute that command
    - if it is a letter, place on top of 'result' stack
    - if it is a symbol, place on top of 'symbols' stack
        - if the symbol is ')', move all operators on the 'symbols' stack between the ')' and the first '(' to the 'result' stack, exclusive (i.e. throw out the parentheses) 
        - if the symbol is an operator AND there was a symbol placed before it (i.e. two symbols in a row like *+) AND the more recent symbol has a lower precedence than the second more recent symbol, move all symbols from 'symbols' stack to 'result' stack until you hit a '('

    - infix_to_rpm: Given an infix expression, return the equivalent RPN expression
        - Determine if the infix expression is valid
        - Start two stacks: 'result' and 'symbols'
        - For each letter in the infix expression:
            - execute infix_update_stacks on the letter
        - If there are any more operators in the 'symbols' stack, place on top of 'result' stack
        - return the result stack

File: main.c

    - main:
        - Question to user: Infix or RPN (for input)?
        - accepts input of a expression
        - Checks if expression is valid infix/RPN using is_valid_expression()
        - if user selected 'infix', call infix_to_rpm
        - if user selected 'rpn', call rpm_to_infix'
        - print result, or error if one is thrown
