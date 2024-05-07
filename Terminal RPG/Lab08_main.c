// **** Include libraries here ****
// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//CSE013E Support Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"


// User libraries


// **** Set any macros or preprocessor directives here ****
#define GAMING 1
#define DIRECTION_ERROR 2
// **** Declare any data types here ****

// **** Define any variables here ****

// **** Declare any function prototypes here ****
int GameLoad(int roomNum);
int GameGetCurrentReqItems(char *reqItems);

int main() {
    /******************************** Your custom code goes below here ********************************/
    system("clear");
    printf("Compiled on %s %s\n\n", __DATE__, __TIME__);
    printf("Welcome to stabilis's Massively Single Player Offline Role Playing Game!\n");
    printf("--------------------------------------------------------------------------\n\n");
    //init variables
    int derror, ierror;
    char title[50];
    char desc[250];
    int exits;
    char chr;
    int status;

    status = GameInit();
    if (status == STANDARD_ERROR) {
        printf("\033[0;31m");
        printf("Fatal Error\n\n");
        printf("\033[0m");
        FATAL_ERROR();
    }

    while (GAMING) {
        derror = FALSE;
        ierror = FALSE;
        //get title
        GameGetCurrentRoomTitle(title);
        printf("                      ~~~~~");
        printf("\033[0;32m");
        printf(" %s ", title);
        printf("\033[0m");
        printf("~~~~~\n\n");

        //get desc
        GameGetCurrentRoomDescription(desc);
        printf("\033[0;36m");
        printf("Description: ");
        printf("\033[0m");
        printf("%s\n\n", desc);
        
        printf("\033[0;33m");
        printf("Options: ");
        printf("\033[0m");
        
        //check for valid options
        exits = GameGetCurrentRoomExits();
        if ((exits & 0x8) != 0) {
            printf("(n)GO NORTH, ");
        }
        if ((exits & 0x4) != 0) {
            printf("(e)GO EAST, ");
        }
        if ((exits & 0x2) != 0) {
            printf("(s)GO SOUTH, ");
        }
        if ((exits & 0x1) != 0) {
            printf("(w)GO WEST, ");
        }
        printf("(q)QUIT\n\n");
        
        printf("\033[0;35m");
        printf("Choose an option: ");
        printf("\033[0m");
        
        
        //init keystroke counter for inputs longer than 1 error
        int kscount = 0;
        fflush(stdin);
        chr = getchar();
        while (getchar() != '\n') {
            kscount++;
        }
        if (kscount <= 0) {
            //quit branch
            if (chr == 'q') {
                printf("\nThanks for playing!\n\n");
                exit(SUCCESS);
                //go north branch
            } else if ((chr == 'n') && (sizeof (chr) == 1)) {
                status = GameGoNorth();
                if (status == STANDARD_ERROR) {
                    printf("\033[0;31m");
                    printf("\nFatal Error\n\n");
                    printf("\033[0m");
                    FATAL_ERROR();
                } else if (status == DIRECTION_ERROR) {
                    derror = TRUE;
                } else {
                    printf("\nYou go North.\n\n");
                }
                //go east branch
            } else if (chr == 'e') {
                status = GameGoEast();
                if (status == STANDARD_ERROR) {
                    printf("\033[0;31m");
                    printf("\nFatal Error\n\n");
                    printf("\033[0m");
                    FATAL_ERROR();
                } else if (status == DIRECTION_ERROR) {
                    derror = TRUE;
                } else {
                    printf("\nYou go East.\n\n");
                }
                //go south branch
            } else if (chr == 's') {
                status = GameGoSouth();
                if (status == STANDARD_ERROR) {
                    printf("\033[0;31m");
                    printf("\nFatal Error\n\n");
                    printf("\033[0m");
                    FATAL_ERROR();
                } else if (status == DIRECTION_ERROR) {
                    derror = TRUE;
                } else {
                    printf("\nYou go South.\n\n");
                }
                //go west branch
            } else if (chr == 'w') {
                status = GameGoWest();
                if (status == STANDARD_ERROR) {
                    printf("\033[0;31m");
                    printf("\nFatal Error\n\n");
                    printf("\033[0m");
                    FATAL_ERROR();
                } else if (status == DIRECTION_ERROR) {
                    derror = TRUE;
                } else {
                    printf("\nYou go West.\n\n");
                }
                //invalid key branch
            } else {
                system("clear");
                ierror = TRUE;
                printf("\033[0;31m");
                printf("\nPlease enter a valid command.\n\n");
                printf("\033[0m");
            }
            system("clear");
            if (derror == TRUE) {
                printf("\033[0;31m");
                printf("\nYou cannot proceed in that direction\n\n");
                printf("\033[0m");
            }
            if (ierror == TRUE) {
                printf("\033[0;31m");
                printf("\nPlease enter a valid command.\n\n");
                printf("\033[0m");
            }
        } else {
            system("clear");
            printf("\033[0;31m");
            printf("\nPlease enter a valid command.\n\n");
            printf("\033[0m");
        }
    }
    /**************************************************************************************************/
    return (0);
}

