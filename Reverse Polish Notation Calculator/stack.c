/* 
 * File:   stack.c
 * Author: Steven Tabilisma
 *
 * Created on July 13, 2020, 7:43 PM
 */
#include "stack.h"
#include "BOARD.h"
#include <stdio.h>

void StackInit(struct Stack *stack) {
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

int StackPush(struct Stack *stack, double value) {
    if (stack->initialized == TRUE) {
        if (StackIsFull(stack) == FALSE) {
            stack->currentItemIndex++;
            stack->stackItems[stack->currentItemIndex] = value;
            return (SUCCESS);
        } else {
            return (STANDARD_ERROR);
        }
    } else {
        return (STANDARD_ERROR);
    }
}

int StackPop(struct Stack *stack, double *value) {
    if (stack->initialized == TRUE) {
        if (StackIsEmpty(stack) == FALSE) {
            *value = stack->stackItems[stack->currentItemIndex];
            stack->currentItemIndex--;
            return (SUCCESS);
        } else {
            return (STANDARD_ERROR);
        }
    } else {
        return (STANDARD_ERROR);
    }
}

int StackIsEmpty(const struct Stack *stack) {
    if (stack->initialized == TRUE) {
        if (stack->currentItemIndex == -1) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

int StackIsFull(const struct Stack *stack) {
    if (stack->initialized == TRUE) {
        if (stack->currentItemIndex == STACK_SIZE - 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

int StackGetSize(const struct Stack *stack) {
    if (stack->initialized == TRUE) {
        return (stack->currentItemIndex + 1);
    } else {
        return SIZE_ERROR;
    }
}
