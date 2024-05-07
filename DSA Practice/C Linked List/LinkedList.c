// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"

ListItem *LinkedListNew(char *data) {
    //return NULL if parameter NULL
    if (data == NULL) {
        return NULL;
    } else {
        //allocate memory
        ListItem *list = malloc(sizeof (ListItem));
        //create new item with no other objects left or right
        list->previousItem = NULL;
        list->nextItem = NULL;
        list->data = data;
        return list;
    }
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {
    //return NULL if parameter NULL
    if (item == NULL) {
        return NULL;
    } else {
        //allocate memory
        ListItem *newItem = malloc(sizeof (ListItem));
        //if at the end, append the item but with next as NULL
        if (item->nextItem == NULL) {
            newItem->data = data;
            newItem->nextItem = NULL;
            newItem->previousItem = item;
            item->nextItem = newItem;
            return newItem;
        } else {
        //otherwise, insert the item and change the proper links
            newItem->data = data;
            newItem->nextItem = item->nextItem;
            newItem->previousItem = item;
            item->nextItem = newItem;
            newItem->nextItem->previousItem = newItem;
            return newItem;
        }
    }
}

char *LinkedListRemove(ListItem * item) {
    //return NULL if parameter NULL
    if (item == NULL) {
        return NULL;
    } else {
        //if at the beginning
        if (item->previousItem == NULL) {
            //make next item the start of list
            item->nextItem->previousItem = NULL;
            //break connections to its next
            item->nextItem = NULL;
        //if at the end
        } else if (item->nextItem == NULL) {
            //make previous item end of the list
            item->previousItem->nextItem = NULL;
            //break connections to its previous
            item->previousItem = NULL;
        //if in the middle
        } else {
            //connect the links between the items on the left and right of item
            item->previousItem->nextItem = item->nextItem;
            item->nextItem->previousItem = item->previousItem;
            item->nextItem = NULL;
            item->previousItem = NULL;
        }
        return item->data;
    }
}

int LinkedListSize(ListItem * list) {
    //return NULL if parameter NULL
    if (list == NULL) {
        return NULL;
    } else {
        //start counter
        int i = 1;
        //find last item
        ListItem* lastItem = LinkedListGetLast(list);
        //starting form the last item, increment counter and
        //move until previous is null
        while (lastItem->previousItem != NULL) {
            lastItem = lastItem->previousItem;
            i++;
        }
        return i;
    }
}

ListItem * LinkedListGetFirst(ListItem * list) {
    //return NULL if parameter NULL
    if (list == NULL) {
        return NULL;
    } else {
        //iterate until the previous item is NULL, return current item
        while (list->previousItem != NULL) {
            list = list->previousItem;
        }
        return list;
    }
}

ListItem * LinkedListGetLast(ListItem * list) {
    //return NULL if parameter NULL
    if (list == NULL) {
        return NULL;
    } else {
        //iterate until the next item is NULL, return current item
        while (list->nextItem != NULL) {
            list = list->nextItem;
        }
        return list;
    }
}

int LinkedListSwapData(ListItem *firstItem, ListItem * secondItem) {
    //return NULL if parameter NULL
    if ((firstItem == NULL) || (secondItem == NULL)) {
        return STANDARD_ERROR;
    } else {
        //create an empty temp list
        ListItem* tempItem = LinkedListNew("temp");
        //store first data in temp
        tempItem->data = firstItem->data;
        //move second data to first data spot
        firstItem->data = secondItem->data;
        //move temp data to second spot
        secondItem->data = tempItem->data;
        return SUCCESS;
    }

}

int LinkedListPrint(ListItem * list) {
    //find start
    ListItem* startItem = LinkedListGetFirst(list);
    //return NULL if parameter NULL
    if (startItem == NULL) {
        return STANDARD_ERROR;
    } else {
        //print first item
        printf("%s\n", startItem->data);
        //iterate though printing all items until the next is NULL
        while (startItem->nextItem != NULL) {
            printf("%s\n", startItem->nextItem->data);
            startItem = startItem->nextItem;
        }
        return SUCCESS;
    }
}
