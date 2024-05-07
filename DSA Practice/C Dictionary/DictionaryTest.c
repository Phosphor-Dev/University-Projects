/*********************************************************************************
* Steven Tabilisma, stabilis
* 2021 Spring CSE101 PA7
* DictionaryTest.c
*********************************************************************************/


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(){

   VAL_TYPE x;

   printf("-Dictionary Test Program-\n");

   Dictionary A = newDictionary(0);

   printf("-Testing Insert-\n");

   insert(A, "a", 1);
   insert(A, "b", 1);
   insert(A, "c", 1);
   insert(A, "d", 1);
   insert(A, "e", 1);
   insert(A, "f", 1);

   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   printf("-Testing Delete-\n");

   delete(A, "a");
   delete(A, "d");
   delete(A, "f");

   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   printf("-Inserting Duplicates-\n");

   insert(A, "a", 1);
   insert(A, "b", 1);
   insert(A, "c", 1);
   insert(A, "d", 1);
   insert(A, "e", 1);
   insert(A, "f", 1);
   insert(A, "f", 1);

   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   printf("-Printing Backwards-\n");

    printf("reverse B:\n");
    for(x=beginReverse(A); currentVal(A)!=VAL_UNDEF; x=prev(A)){
        printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
    }
    printf("\n\n");

    freeDictionary(&A);

}