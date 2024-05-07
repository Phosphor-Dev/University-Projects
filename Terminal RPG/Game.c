// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

int GameLoad(int roomNum);
int GameGetCurrentReqItems(char *reqItems);

#define DIRECTION_ERROR 2

typedef struct {
    int roomNumber;
    int titleLength;
    int reqItemsLength;
    int descLength;
    int itemsLength;

    int nExit;
    int eExit;
    int sExit;
    int wExit;

    char title[50];
    char reqItems[10];
    char desc[250];
    char items[10];
} Room;

Room currentRoom;

int GameGoNorth(void) {
    //check for valid loadable room then load
    if (currentRoom.nExit == 0) {
        return DIRECTION_ERROR;
    } else if (currentRoom.nExit != 0) {
        int status;
        status = GameLoad(currentRoom.nExit);
        if (status == STANDARD_ERROR) {
            return STANDARD_ERROR;
        }
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoEast(void) {
    //check for valid loadable room then load
    if (currentRoom.eExit == 0) {
        return DIRECTION_ERROR;
    } else if (currentRoom.eExit != 0) {
        int status;
        status = GameLoad(currentRoom.eExit);
        if (status == STANDARD_ERROR) {
            return STANDARD_ERROR;
        }
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoSouth(void) {
    //check for valid loadable room then load
    if (currentRoom.sExit == 0) {
        return DIRECTION_ERROR;
    } else if (currentRoom.sExit != 0) {
        int status;
        status = GameLoad(currentRoom.sExit);
        if (status == STANDARD_ERROR) {
            return STANDARD_ERROR;
        }
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameGoWest(void) {
    //check for valid loadable room then load
    if (currentRoom.wExit == 0) {
        return DIRECTION_ERROR;
    } else if (currentRoom.wExit != 0) {
        int status;
        status = GameLoad(currentRoom.wExit);
        if (status == STANDARD_ERROR) {
            return STANDARD_ERROR;
        }
        return SUCCESS;
    } else {
        return STANDARD_ERROR;
    }
}

int GameInit(void) {
    //load the start room and data
    int status;
    currentRoom.roomNumber = STARTING_ROOM;
    status = GameLoad(STARTING_ROOM);
    if (status == STANDARD_ERROR) {
        return STANDARD_ERROR;
    } else {
        return SUCCESS;
    }
}

int GameLoad(int roomNum) {
    //title length and text
    FILE *filePointer;
    char roomName[50];
    sprintf(roomName, "RoomFiles/room%d.txt", roomNum);
    filePointer = fopen(roomName, "rb");
    if (filePointer == NULL) {
        return STANDARD_ERROR;
    }
    fseek(filePointer, 3, SEEK_SET);
    currentRoom.titleLength = fgetc(filePointer);
    fseek(filePointer, 0, SEEK_CUR);
    fgets(currentRoom.title, (currentRoom.titleLength + 1), filePointer);

    //required items length and item
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.reqItemsLength = fgetc(filePointer);
    int reqItem;
    int requirements = STANDARD_ERROR;
    if (currentRoom.reqItemsLength != 0) {
        for (int i = 0; i < currentRoom.reqItemsLength; i++) {
            fseek(filePointer, 0, SEEK_CUR);
            reqItem = fgetc(filePointer);
            requirements = FindInInventory(reqItem);
            if (requirements == STANDARD_ERROR) {
                break;
            }
        }
    }

    //desc length and text
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.descLength = fgetc(filePointer);
    fseek(filePointer, 0, SEEK_CUR);
    fgets(currentRoom.desc, (currentRoom.descLength + 1), filePointer);

    //items in room length and text
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.itemsLength = fgetc(filePointer);
    int cItem;
    if (currentRoom.itemsLength != 0) {
        for (int j = 0; j < currentRoom.itemsLength; j++) {
            fseek(filePointer, 0, SEEK_CUR);
            cItem = fgetc(filePointer);
            AddToInventory(cItem);
        }
    }

    //exits
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.nExit = fgetc(filePointer);
    //printf("\n%d\n", currentRoom.nExit);
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.eExit = fgetc(filePointer);
    //printf("\n%d\n", currentRoom.eExit);
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.sExit = fgetc(filePointer);
    //printf("\n%d\n", currentRoom.sExit);
    fseek(filePointer, 0, SEEK_CUR);
    currentRoom.wExit = fgetc(filePointer);
    //printf("\n%d\n", currentRoom.wExit);


    //if first requirements fail, overwrite data with second version
    if ((requirements == STANDARD_ERROR) && (currentRoom.reqItemsLength != 0)) {
        //required items length and item
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.reqItemsLength = fgetc(filePointer);
        requirements = STANDARD_ERROR;
        if (currentRoom.reqItemsLength != 0) {
            for (int k = 0; k < currentRoom.reqItemsLength; k++) {
                fseek(filePointer, 0, SEEK_CUR);
                reqItem = fgetc(filePointer);
                requirements = FindInInventory(reqItem);
                if (requirements == STANDARD_ERROR) {
                    break;
                }
            }
        }

        //desc length and text
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.descLength = fgetc(filePointer);
        fseek(filePointer, 0, SEEK_CUR);
        fgets(currentRoom.desc, (currentRoom.descLength + 1), filePointer);

        //items in room length and text
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.itemsLength = fgetc(filePointer);
        int cItem2;
        if (currentRoom.itemsLength != 0) {
            for (int l = 0; l < currentRoom.itemsLength; l++) {
                fseek(filePointer, 0, SEEK_CUR);
                cItem2 = fgetc(filePointer);
                AddToInventory(cItem2);
            }
        }

        //exits
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.nExit = fgetc(filePointer);
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.eExit = fgetc(filePointer);
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.sExit = fgetc(filePointer);
        fseek(filePointer, 0, SEEK_CUR);
        currentRoom.wExit = fgetc(filePointer);
    }

    fclose(filePointer);
    return (SUCCESS);
}

int GameGetCurrentRoomTitle(char *title) {
    strcpy(title, currentRoom.title);
    return currentRoom.titleLength;
}

int GameGetCurrentRoomDescription(char *desc) {
    strcpy(desc, currentRoom.desc);
    return currentRoom.descLength;
}

uint8_t GameGetCurrentRoomExits(void) {
    uint8_t exits = 0x0;
    if (currentRoom.nExit != 0) {
        exits = exits | 0x8;
    }
    if (currentRoom.eExit != 0) {
        exits = exits | 0x4;
    }
    if (currentRoom.sExit != 0) {
        exits = exits | 0x2;
    }
    if (currentRoom.wExit != 0) {
        exits = exits | 0x1;
    }
    return exits;
}
