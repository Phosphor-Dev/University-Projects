#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"

int main(void) {
    BOARD_Init();

    printf("\n\nWelcome to stabilis's LinkedListTest.c, compiled on %s %s.\n\n", __DATE__, __TIME__);

    int lln = 0, llca = 0, llr = 0, lls = 0,
            llgf = 0, llgl = 0, llsd = 0, llp = 0, null = 0;

    printf("Testing LinkedListNew()\n\n");

    printf("Creating new list by passing \"Spooky\"...\n");
    ListItem* List1 = LinkedListNew("Spooky");

    printf("Expecting return of: \"Spooky\"...\n");
    if (List1 != NULL) {
        printf("Data returned by returned pointer: %s\n", List1->data);
        printf("Success! Test Passed.\n\n");
        lln++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Creating new list by passing \"Scary\"...\n");
    ListItem* List2 = LinkedListNew("Scary");

    printf("Expecting return of: \"Scary\"...\n");
    if (List2 != NULL) {
        printf("Data returned by pointer: %s\n", List2->data);
        printf("Success! Test Passed.\n\n");
        lln++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************

    printf("Testing LinkedListCreateAfter()\n\n");

    printf("Creating a new list by passing \"past\"...\n");
    ListItem* List3 = LinkedListNew("past");
    printf("Adding new object \"future\" to the end of the created list...\n");
    ListItem* List4 = LinkedListCreateAfter(List3, "future");
    printf("Printing items in the list relative to the head...\n");
    printf("%s\n", List3->data);
    printf("%s\n", List4->data);

    if ((List3->nextItem == List4) && (List4->previousItem = List3)) {
        printf("Success! Test Passed.\n\n");
        llca++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Adding new object \"present\" to the  middle of the created list...\n");
    ListItem* List5 = LinkedListCreateAfter(List3, "present");
    printf("Printing items in the list relative to the added item...\n");
    printf("%s\n", List3->data);
    printf("%s\n", List5->data);
    printf("%s\n", List4->data);

    if ((List3->nextItem == List5) && (List4->previousItem = List5)) {
        printf("Success! Test Passed.\n\n");
        llca++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************

    printf("Testing LinkedListRemove()\n\n");
    printf("Removing object \"present\" from the created list...\n");
    char *List6 = LinkedListRemove(List5);
    printf("Data returned by function: %s\n", List6);
    printf("Printing items in the list...\n");
    printf("%s\n", List3->data);
    printf("%s\n", List4->data);
    if ((List3->nextItem == List4) && (List4->previousItem = List3)) {
        printf("Success! Test Passed.\n\n");
        llr++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Removing object \"future\" from the created list...\n");
    char *List7 = LinkedListRemove(List4);
    printf("Data returned by function: %s\n", List7);
    printf("Printing items in the list...\n");
    printf("%s\n", List3->data);
    if (List3->nextItem == NULL) {
        printf("Success! Test Passed.\n\n");
        llr++;
    } else {
        printf("Test failed. \n\n");
    }

    //**************************************************************************

    printf("Testing LinkedListSize()\n\n");
    printf("Creating a list with 5 items...\n");
    ListItem* List8 = LinkedListNew("past past");
    ListItem* List9 = LinkedListCreateAfter(List8, "past");
    ListItem* List10 = LinkedListCreateAfter(List9, "present");
    ListItem* List11 = LinkedListCreateAfter(List10, "future");
    ListItem* List12 = LinkedListCreateAfter(List11, "future future");
    printf("Printing items in the list...\n");
    printf("%s\n", List8->data);
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List12->data);
    printf("Checking for size 5...\n");
    int size1 = LinkedListSize(List10);
    if (size1 == 5) {
        printf("Success! Test Passed.\n\n");
        lls++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Removing first item...\n");
    char *List13 = LinkedListRemove(List8);
    printf("Printing items in the list...\n");
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List12->data);
    printf("Checking for size 4...\n");
    size1 = LinkedListSize(List9);
    if (List13 != NULL) {
        printf("Success! Test Passed.\n\n");
        lls++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Removing last item...\n");
    char *List14 = LinkedListRemove(List12);
    printf("Printing items in the list...\n");
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("Checking for size 3...\n");
    size1 = LinkedListSize(List11);
    if (List14 != NULL) {
        printf("Success! Test Passed.\n\n");
        lls++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************

    printf("Testing LinkedListGetFirst()\n\n");
    printf("Printing items in the list...\n");
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("Checking output given middle object in the list...\n");
    ListItem* List15 = LinkedListGetFirst(List10);
    if (List15 == List9) {
        printf("Success! Test Passed.\n\n");
        llgf++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Checking output given last object in the list...\n");
    List15 = LinkedListGetFirst(List10);
    if (List15 == List9) {
        printf("Success! Test Passed.\n\n");
        llgf++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Checking output given first object in the list...\n");
    List15 = LinkedListGetFirst(List9);
    if (List15 == List9) {
        printf("Success! Test Passed.\n\n");
        llgf++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************

    printf("Testing LinkedListGetLast()\n\n");
    printf("Checking output given middle object in the list...\n");
    List15 = LinkedListGetLast(List10);
    if (List15 == List11) {
        printf("Success! Test Passed.\n\n");
        llgl++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Checking output given last object in the list...\n");
    List15 = LinkedListGetLast(List10);
    if (List15 == List11) {
        printf("Success! Test Passed.\n\n");
        llgl++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Checking output given first object in the list...\n");
    List15 = LinkedListGetLast(List10);
    if (List15 == List11) {
        printf("Success! Test Passed.\n\n");
        llgl++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************
    printf("Testing LinkedListSwapData()\n\n");
    printf("Printing items in the list...\n");
    ListItem* List16 = LinkedListCreateAfter(List10, "past past");
    ListItem* List17 = LinkedListCreateAfter(List11, "future future");
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List16->data);
    printf("%s\n", List17->data);
    printf("Swapping item 4 and item 1.\n");
    int List18 = LinkedListSwapData(List9, List16);
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List16->data);
    printf("%s\n", List17->data);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llsd++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Swapping item 4 and item 2.\n");
    List18 = LinkedListSwapData(List10, List16);
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List16->data);
    printf("%s\n", List17->data);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llsd++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Swapping item 4 and item 3.\n");
    List18 = LinkedListSwapData(List11, List16);
    printf("%s\n", List9->data);
    printf("%s\n", List10->data);
    printf("%s\n", List11->data);
    printf("%s\n", List16->data);
    printf("%s\n", List17->data);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llsd++;
    } else {
        printf("Test failed.\n\n");
    }

    //**************************************************************************
    printf("Testing LinkedListPrint()\n\n");
    printf("Printing items in the list by calling function and"
            " passing first item...\n");
    List18 = LinkedListPrint(List9);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llp++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Printing items in the list by calling function and"
            " passing middle item...\n");
    List18 = LinkedListPrint(List11);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llp++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Printing items in the list by calling function and"
            " passing middle item...\n");
    List18 = LinkedListPrint(List17);
    if (List18 == SUCCESS) {
        printf("Success! Test Passed.\n\n");
        llp++;
    } else {
        printf("Test failed.\n\n");
    }
    //**************************************************************************

    printf("Testing NULL cases for all functions.\n\n");
    printf("-----------------------------------------\n");

    printf("Testing LinkedListNew()\n\n");
    ListItem* List19 = LinkedListNew(NULL);
    if (List19 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Testing LinkedListCreateAfter()\n\n");
    List19 = LinkedListCreateAfter(NULL, NULL);
    if (List19 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Testing LinkedListRemove()\n\n");
    char *List20 = LinkedListRemove(NULL);
    if (List20 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Testing LinkedListSize()\n\n");
    int List21 = LinkedListSize(NULL);
    if (List21 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }

    printf("Testing LinkedListGetFirst()\n\n");
    List19 = LinkedListGetFirst(NULL);
    if (List19 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }
    
    printf("Testing LinkedListGetLast()\n\n");
    List19 = LinkedListGetLast(NULL);
    if (List19 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }
    printf("Testing LinkedListSwapData()\n\n");
    List21 = LinkedListSwapData(NULL, NULL);
    if (List21 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }
    
    printf("Testing LinkedListPrint()\n\n");
    List21 = LinkedListPrint(NULL);
    if (List21 == NULL) {
        printf("Success! Test Passed.\n\n");
        null++;
    } else {
        printf("Test failed.\n\n");
    }
    
    printf("-----------------------------------------\n");
    printf("Results:\n");
    printf("LinkedListNew(): %d/2\n", lln);
    printf("LinkedListsCreateAfter(): %d/2\n", llca);
    printf("LinkedListRemove(): %d/2\n", llr);
    printf("LinkedListSize(): %d/3\n", lls);
    printf("LinkedListGetFirst(): %d/3\n", llgf);
    printf("LinkedListGetLast(): %d/3\n", llgl);
    printf("LinkedListSwapData(): %d/3\n", llsd);
    printf("LinkedListPrint(): %d/3\n", llp);
    printf("NULL input tests: %d/8\n", null);
  
    BOARD_End();
    while (1);
}
