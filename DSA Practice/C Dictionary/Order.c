/*********************************************************************************
* Steven Tabilisma, stabilis
* 2021 Spring CSE101 PA7
* Order.c
*********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Dictionary.h"

#define MAX_LEN 300
#define LINE "******************************************************\n"

int main(int argc, char *argv[])
{
    int i = 0;
    char *string;
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];
    char numLine[MAX_LEN];
    Dictionary dict = newDictionary(0);
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    line_count = 0;
    while (fgets(numLine, MAX_LEN, in) != NULL) line_count++;
    rewind(in);
    int num[line_count];

    char **stringArray = malloc(line_count * sizeof(char *));
    for (int i = 0; i < line_count; i++)
    {
        stringArray[i] = (char *)malloc(MAX_LEN);
        num[i] = i + 1;
    }
    
    while (i < line_count && fgets(line, MAX_LEN, in))
    {
        if (strcmp(line, "\n") != 0) string = strtok(line, "\n");
        else string = "";
        strcpy(stringArray[i], string);
        insert(dict, stringArray[i], &num[i]);
        i++;
    }
    fprintf(out, LINE "PRE-ORDER:\n" LINE);
    printDictionary(out, dict, "pre");
    fprintf(out, "\n\n" LINE "IN-ORDER:\n" LINE);
    printDictionary(out, dict, "in");
    fprintf(out, "\n\n" LINE "POST-ORDER:\n" LINE);
    printDictionary(out, dict, "post");
    freeDictionary(&dict);

    for (int i = 0; i < line_count; i++) free(stringArray[i]);
    free(stringArray);

    // close files
    fclose(in);
    fclose(out);

    return (0);
}
