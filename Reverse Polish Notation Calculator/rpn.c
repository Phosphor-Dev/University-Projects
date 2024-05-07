/* 
 * File:   rpn.c
 * Author: Steven Tabilisma
 *
 * Created on July 13, 2020, 7:42 PM
 */
#include "stack.h"
#include "BOARD.h"
#include <stdio.h>
#include "rpn.h"
#include <string.h>
#include <stdlib.h>

int RPN_Evaluate(char * rpn_string, double * result) {
    /*RPN_NO_ERROR = 0,
    -RPN_ERROR_STACK_OVERFLOW,
    -RPN_ERROR_STACK_UNDERFLOW,
    -RPN_ERROR_INVALID_TOKEN,
    -RPN_ERROR_DIVIDE_BY_ZERO,
    -RPN_ERROR_TOO_FEW_ITEMS_REMAIN,
    -RPN_ERROR_TOO_MANY_ITEMS_REMAIN*/

    //init stack and filter char
    struct Stack expr;
    StackInit(&expr);
    char filter[] = " ";

    /*
    int tokens = 0;
    //total tokens counter
    char *temp = strtok(rpn_string, filter);
    while (temp != NULL) {
        tokens++;
        temp = strtok(NULL, " ");
    }
    printf("Token count: %d\n", tokens);
        if ((tokens == 1) && atof(item) != 00) {
            StackPush(&expr, *result);
            return RPN_NO_ERROR;
        }
     */

    //initialize tokenization and loop through all tokens
    char *item = strtok(rpn_string, filter);
    
    if ((strcmp(item, "+") == 0) || (strcmp(item, "-") == 0)
           || (strcmp(item, "*") == 0) || (strcmp(item, "/") == 0)){
        return RPN_ERROR_STACK_UNDERFLOW;
    }
    
    while (item != NULL) {

        //if there are no items entered return error
        int strLength = strlen(item);
        if (strLength == 0) {
            return RPN_ERROR_INVALID_TOKEN;
        }
        
        //declare variables
        double operand1, operand2, out;
        //printf("    Current Item: %s\n", item);
        //check for full stack
        if (StackIsFull(&expr) == TRUE) {
            return RPN_ERROR_STACK_OVERFLOW;
        }

        if (strcmp(item, "0") == 0 || strcmp(item, "0.0") == 0) {
            StackPush(&expr, 0.0);
        } else if ((atof(item) == 0.0)
                && ((strcmp(item, "+") != 0)
                && (strcmp(item, "-") != 0)
                && (strcmp(item, "*") != 0)
                && (strcmp(item, "/")) != 0)) {
            return RPN_ERROR_INVALID_TOKEN;
        } else if ((strcmp(item, "+") != 0)
                && (strcmp(item, "-") != 0)
                && (strcmp(item, "*") != 0)
                && (strcmp(item, "/") != 0)) {
            double value = strtod(item, NULL);
            StackPush(&expr, value);
        }//branch for addition        
        else if (strcmp(item, "+") == 0) {
            //check for too few operands to calculate
            if (StackGetSize(&expr) <= 1) {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
            } else {
                StackPop(&expr, &operand2);
                StackPop(&expr, &operand1);
                out = operand1 + operand2;
                StackPush(&expr, out);
            }

            //branch for subtraction
        } else if (strcmp(item, "-") == 0) {
            //check for too few operands to calculate
            if (StackGetSize(&expr) <= 1) {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
            } else {
                StackPop(&expr, &operand2);
                StackPop(&expr, &operand1);
                out = operand1 - operand2;
                StackPush(&expr, out);
            }

            //branch for multiplication
        } else if (strcmp(item, "*") == 0) {
            //check for too few operands to calculate
            if (StackGetSize(&expr) <= 1) {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
            } else {
                StackPop(&expr, &operand2);
                StackPop(&expr, &operand1);
                out = operand1 * operand2;
                StackPush(&expr, out);
            }

            //branch for division
        } else if (strcmp(item, "/") == 0) {

            //check for too few operands to calculate
            if (StackGetSize(&expr) <= 1) {
                return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
            } else {
                StackPop(&expr, &operand2);
                StackPop(&expr, &operand1);
                if (operand2 == 0) {
                    return RPN_ERROR_DIVIDE_BY_ZERO;
                } else {
                    out = operand1 / operand2;
                    StackPush(&expr, out);
                }
            }
        }
        //increment for next token
        item = strtok(NULL, " ");
    }

    //check if too many items remain in stack at return
    double val;
    StackPop(&expr, &val);
    
    if (StackGetSize(&expr) > 0) {

        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    *result = val;
    return RPN_NO_ERROR;
}

int ProcessBackspaces(char *rpn_sentence) {
    int i = 0, j = 0, k = 0, l = 0;
    char rstring[256];
    int len = strlen(rpn_sentence);
    //(i = 0; i < len; i++) (i = (len - 1); i >= 0; i--)
    for (i = (len - 1); i >= 0; i--){
        //printf("Current Character: %c\n", rpn_sentence[i]);
        if (rpn_sentence[i] == '\b') {
            i--;
            j = j + 2;
        } else {
            rstring[k] = rpn_sentence[i];
            k++;
        }
    }
    rpn_sentence = NULL;
    for (l = (len - j); l >= 0; l--) {
        //printf("Reverse Character: %c\n", rstring[l]);
        strncat(rpn_sentence, &rstring[l], 1);
    }
    
    
    
/*
    //\b = backspace char
    int i = 0, j = 0, k = 0, bkspce = 0;
    char rstring[256];
    int len = strlen(rpn_sentence);
    //(i = 0; i < len; i++) (i = (len - 1); i >= 0; i--)
    for (i = 0; i < len; i++) {
        printf("Current Character: %c\n", rpn_sentence[i]);
        if (rpn_sentence[i] == '\b') {
            if ((j > 0) && (rpn_sentence[(i + 1)] != '\b')){
                j--;
                j--;
                bkspce++;
                bkspce++;
            }
        } else {
            rstring[j] = rpn_sentence[i];
        }
        j++;
    }
    *rpn_sentence = NULL;
    for (k = 0; k < (len - bkspce); k++) {
        printf("Reverse Character: %c\n", rstring[k]);
        strncat(rpn_sentence, &rstring[k], 1);
    }
 */
    return (1);
}
/*
char *point, *track;
for (point = track = rpn_sentence; *point != '\0'; point++) {
    if (*point == '\b') {
        if (track != rpn_sentence) {
            track--;
        }
        continue;
    }
 *track++ = *point;
}
 *track = '\0';
return 0;
}   */
