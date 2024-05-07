//-----------------------------------------------------------------------------
// List.h
// Header file for List.c
// Written by Steven Tabilisma for CSE101 SPRING 2021  | stabilis@ucsc.edu
//-----------------------------------------------------------------------------

#ifndef List_H_INCLUDE_

// Exported type --------------------------------------------------------------
typedef struct ListObj *List;

// Constructors-Destructors ---------------------------------------------------

List newList(void);
void freeList(List *pQ);

// Access functions -----------------------------------------------------------

int length(List Q);         // Returns the Length of the list.
int index(List Q);          // Returns index of cursor element if defined, -1 otherwise.
int front(List Q);          // Returns front element of L. Pre: length()>0.
int back(List Q);           // Returns back element of L. Pre: length()>0.
int get(List Q);            // Returns cursor element of L. Pre: length()>0, index()>=0.
int equals(List A, List B); // Returns true (1) iff Lists A and B are in same.

// Unused Access Functions

int isEmpty(List Q);

// Manipulation procedures ----------------------------------------------------

void clear(List Q);               // Resets L to its original empty state.
void set(List Q, int x);          // Overwrites the cursor elementâ€™s data with x.
void moveFront(List Q);           // If L is non-empty, sets cursor under the front element.
void moveBack(List Q);            // If L is non-empty, sets cursor under the back element.
void movePrev(List Q);            // If cursor is defined and not at front, move cursor forward
void moveNext(List Q);            // If cursor is defined and not at back, move cursor backwards
void prepend(List Q, int x);      // Insert new element into L. insertion takes place before front element.
void append(List Q, int x);       // Insert new element into L. insertion takes place after back element.
void insertBefore(List Q, int x); // Insert new element before cursor.
void insertAfter(List Q, int x);  // Insert new element after cursor.
void deleteFront(List Q);         // Delete the front element. Pre: length()>0.
void deleteBack(List Q);          // Delete the back element. Pre: length()>0.
void delete (List Q);             // Delete cursor element, making cursor undefined.
void deleteNode(List Q);          // Helper Function for delete.

// Other Functions ------------------------------------------------------------
void printList(FILE *out, List Q); // Prints to the file pointed to by out.
List copyList(List Q);             // Returns a new List representing the same integer sequence as L.
int orderedInsert(List L, int i);
#endif