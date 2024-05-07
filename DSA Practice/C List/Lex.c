//-----------------------------------------------------------------------------
//Lex.c
//Implements List.c in order to sort provided .txt files.
// Written by Steven Tabilisma for CSE101 Spring 2021  | stabilis@ucsc.edu
//-----------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char *argv[])
{
    FILE *in, *out;
    List cList = newList();
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    char line[MAX_LEN];
    int lines = 1;
    char numLine[MAX_LEN];
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    while (fgets(numLine, MAX_LEN, in) != NULL)
    {
        lines++;
    }
    fseek(in, 0, SEEK_SET);
    lines++;
    char strings[lines][MAX_LEN];

    int i = 0;
    int j = 0;
    while (fgets(line, MAX_LEN, in))
    {
        strcpy(strings[i], line);
        i++;
    }
    append(cList, 0);
    lines -= 1;
    int x;
    int check = 0;
    for (i = 1; i < lines; i++)
    {
        moveFront(cList);
        for (j = 0; index(cList) >= 0; j++)
        {
            x = get(cList);
            check = 0;
            if (index(cList) == length(cList) - 1 && strcmp(strings[i], strings[x]) > 0)
            {
                append(cList, i);
                check = 1;
            }
            if (check)
            {
                break;
            }
            if(strcmp(strings[i], strings[x]) <= 0)
            {
                insertBefore(cList, i);
                check = 1;
            }
            if (check)
            {
                break;
            }
            if (check == 0)
            {
                moveNext(cList);
            }
        }
    }
    moveFront(cList);
    while (index(cList) >= 0)
    {
        char *text = strings[get(cList)];
        fprintf(out, "%s", text);
        moveNext(cList);
    }
    fclose(in);
    fclose(out);
    freeList(&cList);
    return (0);
}
