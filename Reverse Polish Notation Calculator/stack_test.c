// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

//Declaration of functions
void StackInit(struct Stack *stack);
int StackPush(struct Stack *stack, double value);
int StackPop(struct Stack *stack, double *value);
int StackIsEmpty(const struct Stack *stack);
int StackIsFull(const struct Stack *stack);
int StackGetSize(const struct Stack *stack);

int main() {
    BOARD_Init();

    printf("\n###### Beginning stabilis's stack test harness: #####\n\n");
    //pass counters
    int init = 0, push = 0, pop = 0, empty = 0, full = 0, size = 0;
    
    //current item index
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    
    printf("TEST 1\n");
    printf("Declaring stack...\n");
    struct Stack stack = {};
    printf("Initializing...\n");
    StackInit(&stack);
    printf("Expecting stack status to be initialized.\n");
    if (stack.initialized == TRUE) {
        printf("Stack status: Initialized\n");
        printf("passed\n\n");
        init++;
    } else {
        printf("failed\n\n");
    }
    
    printf("TEST 2\n");
    printf("Declaring stack...\n");
    struct Stack unstack = {};
    printf("Not initializing stack...\n");
    printf("Expecting stack status to be uninitialized.\n");
    if (unstack.initialized == FALSE) {
        printf("Stack status: Uninitialized\n");
        printf("passed\n\n");
        init++;
    } else {
        printf("failed\n\n");
    }
    
    //stack push & pop
    printf("Does StackPush() push, and does StackPop() pop?\n");
    
    printf("TEST 1 & 2\n");
    printf("Pushing: 2.000000... \n");
    StackPush(&stack, 2.0);
    printf("Pushing: 3.000000... \n");
    StackPush(&stack, 3.0);
    printf("Expecting currentItemIndex to equal 1.\n");
    if (stack.currentItemIndex == 1) {
        printf("passed\n\n");
        push++;
        push++;
    } else {
        printf("failed\n\n");
    }

    //stack pop
    double value;
    printf("TEST 1\n");
    printf("Popping: 3.000000... \n");
    StackPop(&stack, &value);
    printf("Value popped: %f\n", value);
    if (value == 3.0) {
        printf("passed\n\n");
        pop++;
    } else {
        printf("failed\n\n");
    }
    
    printf("TEST 2\n");
    printf("Popping: 2.000000... \n");
    StackPop(&stack, &value);
    printf("Value popped: %f\n", value);
    if (value == 2.0) {
        printf("passed\n\n");
        pop++;
    } else {
        printf("failed\n\n");
    }

    //stack empty
    printf("Does StackIsEmpty() work?\n");
    printf("TEST 1\n");
    printf("Expected result: TRUE\n");
    if (StackIsEmpty(&stack) == TRUE) {
        printf("Actual result: TRUE\n");
        printf("passed\n\n");
        empty++;
    } else {
        printf("Actual result: FALSE\n");
        printf("failed\n\n");
    }
    
    printf("TEST 2\n");
    printf("Pushing 3 items to the stack...\n");
    StackPush(&stack, 0.0);
    StackPush(&stack, 1.0);
    StackPush(&stack, 2.0);
    printf("Expected result: FALSE\n");
    if (StackIsEmpty(&stack) == FALSE) {
        printf("Actual result: FALSE\n");
        printf("passed\n\n");
        empty++;
    } else {
        printf("Actual result: TRUE\n");
        printf("failed\n\n");
    }
    
    //stack full
    printf("Does StackIsFull() work?\n");
    printf("TEST 1\n");
    printf("Filling the stack...\n");
    StackPush(&stack, 3.0);
    StackPush(&stack, 4.0);
    StackPush(&stack, 5.0);
    StackPush(&stack, 6.0);
    StackPush(&stack, 7.0);
    StackPush(&stack, 8.0);
    StackPush(&stack, 9.0);
    StackPush(&stack, 10.0);
    StackPush(&stack, 11.0);
    StackPush(&stack, 12.0);
    StackPush(&stack, 13.0);
    StackPush(&stack, 14.0);
    StackPush(&stack, 15.0);
    StackPush(&stack, 16.0);
    StackPush(&stack, 17.0);
    StackPush(&stack, 18.0);
    StackPush(&stack, 19.0);
    
    printf("Expected result: TRUE\n");
    if (StackIsFull(&stack) == TRUE) {
        printf("Actual result: TRUE\n");
        printf("passed\n\n");
        full++;
    } else {
        printf("Actual result: FALSE\n");
        printf("failed\n\n");
    }

    printf("TEST 2\n");
    printf("Popping 5 items from the stack...\n");
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    printf("Expected result: FALSE\n");
    if (StackIsFull(&stack) == FALSE) {
        printf("Actual result: FALSE\n");
        printf("passed\n\n");
        full++;
    } else {
        printf("Actual result: TRUE\n");
        printf("failed\n\n");
    }

    //get size
    printf("Does StackGetSize() work?\n");
    printf("TEST 1\n");
    printf("Expected stack size: 15\n");
    if (StackGetSize(&stack) == 15) {
        printf("Actual result: %d\n", StackGetSize(&stack));
        printf("passed\n\n");
        size++;
    } else {
        printf("failed\n\n");
    }
    
    printf("TEST 2\n");
    printf("Popping 3 items from the stack...\n");
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    StackPop(&stack, &value);
    printf("Expected stack size: 12\n");
    if (StackGetSize(&stack) == 12) {
        printf("Actual result: %d\n", StackGetSize(&stack));
        printf("passed\n\n");
        size++;
    } else {
        printf("failed\n\n");
    }
    printf("Results:\n");
    printf("StackInit() tests passed: %d/2\n", init);
    printf("StackPush() tests passed: %d/2\n", push);
    printf("StackPop() tests passed: %d/2\n", pop);
    printf("StackIsEmpty() tests passed: %d/2\n", empty);
    printf("StackIsFull() tests passed: %d/2\n", full);
    printf("StackGetSize() tests passed: %d/2\n", size);
    
    BOARD_End();
    while (1);
    return 0;
}


