/*********************************************************************************
* Steven, stabilis
* 2021 Spring CSE101 PA4
* Shuffle.cpp
*********************************************************************************/

#include <iostream>
#include <string>
#include "List.h"

using namespace std;
void shuffle(List &in);

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    printf("deck size\tshuffle count\n");
    printf("------------------------------\n");
    for (int i = 1; i <= num; i++)
    {
        printf("%d", i);
        List L;
        List temp;
        int count = 1;
        for (int j = 0; j <= i; j++) L.insertBefore(j);
        L.eraseBefore();
        temp = L;
        shuffle(L);
        while ((L == temp) == 0)
        {
            shuffle(L);
            count++;
        }
        printf("\t\t\t%d", count);
        printf("\n");
    }
    return (EXIT_SUCCESS);
}

void shuffle(List &in)
{
    List A;
    List B;
    int left;
    int size;
    int right;
    int insert;
    size = in.size();
    if(in.size() % 2 == 0)
    {
        left = in.size() / 2;
        right = in.size() / 2;
    }
    else
    {
        left = in.size() / 2;
        right = (in.size() / 2) + 1;
    }
    in.moveFront();
    for(int i = 0; i < left; i++)
    {
        insert = in.moveNext();
        A.insertBefore(insert);
    }
    for(int i = 0; i < right; i++)
    {
        insert = in.moveNext();
        B.insertBefore(insert);
    }
    in.clear();
    A.moveFront();
    B.moveFront();
    for(int i = 0; i < size; i++)
    {
        if(i % 2 == 0) in.insertBefore(B.moveNext());
        if(i % 2 != 0) in.insertBefore(A.moveNext());
    }
    A.clear();
    B.clear();
}
