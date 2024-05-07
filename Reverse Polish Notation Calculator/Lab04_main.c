// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "stack.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to stabilis's RPN calculator.  Compiled on %s %s\n", __DATE__, __TIME__);
    while (1) {
        printf("Enter floats and + - / * in RPN format:\n");
        fgets(rpn_sentence, 10000, stdin);
        if (strlen(rpn_sentence) > MAX_INPUT_LENGTH) {
            printf("Expression entered contains too many characters.(Limit: 60)\n");
        } else {
            char *remove;
            if ((remove = strchr(rpn_sentence, '\n')) != NULL) {
                *remove = '\0';
            }
            int out = RPN_Evaluate(rpn_sentence, &result);
            if (out == RPN_ERROR_STACK_OVERFLOW) {
                printf("Stack overflow error. "
                        "Expression contains too many operands.\n");
            } else if (out == RPN_ERROR_STACK_UNDERFLOW) {
                printf("Stack underflow error. "
                        "Expression contains too few operands.\n");
            } else if (out == RPN_ERROR_INVALID_TOKEN) {
                printf("Invalid token error. "
                        "One or more entered tokens are invalid.\n");
            } else if (out == RPN_ERROR_DIVIDE_BY_ZERO) {
                printf("Divide by zero error. "
                        "Expression attempts to divide by zero.\n");
            } else if (out == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
                printf("Invalid expression format entered. "
                        "The stack at this point has no items to calculate with.\n");
            } else if (out == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
                printf("Invalid expression format entered. "
                        "The stack contains more than one item at the point of return\n");
            } else {
                printf("Result = %f\n", result);
            }
        }
    }

    while (1);
}
