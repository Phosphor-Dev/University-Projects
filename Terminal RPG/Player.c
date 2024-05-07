//Steven Tabilisma
// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

char inventory[255];
int capacity = INVENTORY_SIZE;

int AddToInventory(uint8_t item) {
    //check for bag capacity, store in inventory
    if (capacity > 0) {
        inventory[item] = item;
        capacity--;
        return SUCCESS;
    } else {
        printf("\033[0;31m");
        printf("Inventory Full. Item not obtained.\n");
        printf("\033[0m");
        return STANDARD_ERROR;
    }
}

int FindInInventory(uint8_t item) {
    //check for item in inventory
    if (inventory[item] == item) {
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}
