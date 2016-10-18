# RPN/Infix Converter

This is a simple C program that converts a mathematical expression from Reverse Polish Notation to Infix (or vice versa).

This library was written in C99 and uses the [Check](https://libcheck.github.io/check) testing suite. Its only dependencies are Check, GNU make (to build), and GNU GCC (to compile). In addition, `libsubunit-dev` might need to be installed for Check, depending on your operating system - if you get a "Cannot find '-lsubunit'" error from GCC, this would be how to fix it.

To build the script, run `make convert`. To build the testing script, run `make tests`. The executables will be `convert` and `convert_tests`, respectively. `make all` will make both scripts, and `make clean` will remove them as well as any build artifacts.

`convert` takes no arguments, but will prompt the user for an initial expression no longer than 500 characters and the type of conversion. The initial expression must consist of operands in the form of lowercase letters, valid operators (`^`, `/`, `*`, `-`, `+`), and parentheses (`(` and `)` only). 

`convert_tests` will run through all the unit tests contained in the `test/` directory, and also takes no input.

## Library API
The `src/` directory contains the source code for this program:
- `main.c`, containing a way for the user to input an expression and conversion type, and receive the result
- `rpn_to_infix.c`, containing the conversion algorithm for converting an expression from RPN to Infix, as well as several helper functions
- `infix_to_rpn.c`, containing the conversion algorithm for converting an expression from Infix to RPN, as well as several helper functions
- `utilities.c`, containing helper functions shared across the program (mainly to do with character identification), as well as the `append` and `pop` method for the stack.

Header files are contained in `include/`, and unit tests in `test/`, named according to what they test. 

## Conversion Methods

This section contains my solution to the problem. I worked out the algorithms and syntax rules using pencil and paper, without reference to online solutions in any form. Once I had a set of rules that seemed to work, I implemented them, then went through the following loop.

1. Attempt to break what I had with some complex/weird/malformed input in the form of a test
2. Fix the code, using C99 reference websites as necessary
3. Repeat 1 and 2 until I couldn't think of new ways to break the code

Also, note that I use `variable` and `operand` interchangeably throughout the rest of this README

### Pre-conversion Checking

Before an attempt at conversion is made, an attempt is made to determine if the input expression is valid or not. If the expression is invalid, the program will throw an error and exit

#### RPN

A RPN expression is considered valid if:

1. The expression contains EXACTLY `n` variables and `n-1` operators, since all supported operators require 2 operands to execute successfully (so `ab`, `+++` and `-b` are invalid)
2. The expression contains only variables and operators (no parentheses, other symbols/letters, etc.)
3. At no point, starting from the beginning of the expression, should there be the same number of variables and operands (so `a+b` is invalid because at the `+`, there are not enough operators 'behind' it to execute successfully. Same goes for `ab+c--d`, etc.)

#### Infix
An Infix expression is considered valid if:

1. The expression contains EXACTLY `n` variables and `n-1` operators, since all supported operators require 2 operands to execute successfully (so `ab`, `+++` and `-b` are invalid)
2. There are an equal number of `(` and `)` in the expression
3. The expression contains only variables, operators, and parentheses
4. Each substring, defined as a section of an expression contained within parentheses, is also valid, given the criteria above. For example, given the expression `((a+b)+c)+d`, `(a+b)` and `((a+b)+c)` MUST be valid for the full expression to be valid. This allows us to catch expressions like `(a+)b`, which satisfy the first three rules above, but is clearly invalid.

### RPN to Infix

The script first creates a stack of length 50, with each element in the stack able to hold an RPN expression of up to 1000 characters (Any attempt at over/underflow will result in an error being thrown and the program exiting).

For each character in the RPN expression:
- If the character is a variable, append it to the stack
- If the character is an operand:
    - Pop off the top two contents of the stack (if there are fewer that two operators on the stack, report an error and exit)
    - Combine the result of the two pops with the operand, wrapping the result in parentheses
    - Append this new expression to the stack
    
When the loop is done and, assuming the RPN expression was valid, the result will be a single expression on the stack, and that expression with be the infix expression. That expression is returned and printed to the screen. If there is more than one expression remaining on the stack, then there was a syntactical error in the initial expression, and an error is thrown.

As an example, consider the expression `vw/x^yz-*` (Elements in the stack are separated by `,`). The execution loop would look like: 

| Character |        Stack        |
|-----------|---------------------|
|     v     |   v                 |
|     w     |   v, w              |
|     /     |   (v/w)             |
|     x     |   (v/w), x          |
|     ^     |   ((v/w)^x)         |
|     y     |   ((v/w)^x), y      |
|     z     |   ((v/w)^x), y, z   |
|     -     |   ((v/w)^x), (y-z)  |
|     *     |   (((v/w)^x)*(y-z)) |

So, `(((v/w)^x)*(y-z))` would be what is returned to the user. Note that the final expression is wrapped in a set of parentheses. These are technically redundant, but the expression is still valid.

### Infix to RPN


The script creates two stacks, one for variables, and one for symbols (the five valid operators plus `(` and `)`). Both are able to hold up to 1000 characters (Any attempt at over/underflow will result in an error being thrown and the program exiting).

For each character in the RPN expression:
- If the character is a variable, append it to the variable stack
    
- If the character is a symbol:
    - If the character is `)`:
        - Starting from the top of the operator stack, pop off all operators and append them to the variable stack
        - If this loop reaches an `(`, pop it off and terminate the loop
        - If this loop reaches the bottom of the operator stack without having found a `(`, there were mismatched parentheses in the expression, so throw an error
    - If the character `c1` is an operator and the symbol stack is not empty:
        - If the symbol at the top of the symbol stack `c2` is an operator AND either (`c1` is right-associative and has greater precedence than `c2`) OR (`c1` is left-associative and has precedence greater than or equal to `c2`), pop `c2` off the symbol stack and append it to the operator stack. 
        - Repeat this for each operator at the top of the symbol stack, break from this loop if the above is not true
        - Append `c1` to the symbol stack
    - Otherwise, append `c1` to the symbol stack
- Otherwise, this character is invalid - throw an error and exit the program

At the end of this loop, any symbols remaining on the symbol stack are appended to the variable stack, and the contents of the variable stack contain the final RPN expression. If there is a parenthesis on the symbol or variable stack, then we have mismatched parentheses, so throw an error and exit.

As an example, consider the expression `((v/w)^x)*(y-z)` from above. The execution loop would look like this:

| Character |     Variable Stack      | Operator Stack |
|-----------|-------------------------|----------------|
|     (     |                         | (              |
|     (     |                         | (, (           |
|     v     | v                       | (, (           |
|     /     | v                       | (, (, /        |
|     w     | v, w                    | (, (, /        |
|     )     | v, w, /                 | (              |
|     ^     | v, w, /                 | (, ^           |
|     x     | v, w, /, x              | (, ^           |
|     )     | v, w, /, x, ^           |                |
|     *     | v, w, /, x, ^           | *              |
|     (     | v, w, /, x, ^           | *, (           |
|     y     | v, w, /, x, ^, y        | *, (           |
|     -     | v, w, /, x, ^, y        | *, (, -        |
|     z     | v, w, /, x, ^, y, z     | *, (, -        |
|     )     | v, w, /, x, ^, y, z, -  | *              |

At the end, the remaining `*` is appended to the end of the variable stack, and the stack is transformed into a singular string. The result, `vw/x^yz-*`, is identical with the expression we started with in the previous section.

## Syntax Rules

### Infix

Infix notation is mathematical notation in which the operators are placed between operands (e.g. `2*4`). Infix expression are evaluated according to an established order of operations, which means that operators with higher precedence are executed before operators with lower precedence. The order of operations for this script is defined below:

| Operator |     Precedence    |
|----------|-------------------|
|    ^     |      1 (first)    |
|    /     |      2            |
|    *     |      3            |
|    -     |      4            |
|    +     |      5 (last)     |

For example, the expression `2 + 3 * 5` would be evaluated to 17, since the multiplication operator is acted upon first. In cases where the operators have equal precedence, they are simply evaluated from left to right.

Infix expressions may also use parentheses to group subsections of the expression to indicate which parts of the expression need to be evaluated first. For example, the expression `( 2 + 3 ) * 5` would be evaluated to 25, since the expression contained within the parentheses is evaluated first. Put another way, parentheses have a higher precedence than any operator, and must always be evaluated first.

The unary negation operator (e.g. -a to mean "negative a") is not supported by this program.

### Reverse Polish Notation (RPN)
In RPN, operators are placed after their operands (e.g. `2 4 *`). A RPN expression is evaluated from left to right, and there are no parentheses or operator precedence - whatever occurs first in the expression will be evaluated first. The equivalent to `2 + 3 * 5` in the infix section above would be `3 5 * 2 +`, and `( 2 + 3 ) * 5` would become `2 3 + 5 *`.
