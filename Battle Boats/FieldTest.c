
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdint.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

//CE13 standard libraries:
#include "Buttons.h"
#include "Uart1.h"
#include "Oled.h"

// Battleboats Libraries:
#include "BattleBoats.h"
#include "Agent.h"
#include "Negotiation.h"
#include "Message.h"
#include "Field.h"
#include <time.h>   



int main(){
    BOARD_Init();
    TRISE = 0;
    LATE = 0;
    int a,b;
    //initialize CE13 libraries:
    //ButtonsInit();
    OledInit();
    //Print a greeting:
    OledDrawString("This is BattleBoats!\nPress BTN4 to\nchallenge, or wait\nfor opponent.");
    OledUpdate();
    
    printf("-CHECK ONE, AUTO PLACEMENT-\n\n");
    
    printf("1) Init the fields\n");
    
    Field myField;
    Field theirField;
    FieldInit(&myField,&theirField);
    
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", myField.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", theirField.grid[a][b]);
        }
    }
    
    printf("\n\n2) Place ships in myField\n");
    FieldAIPlaceAllBoats(&myField);
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", myField.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", theirField.grid[a][b]);
        }
    }
    
    printf("\n\n3) Place ships in theirField\n");
    FieldAIPlaceAllBoats(&theirField);
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", myField.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", theirField.grid[a][b]);
        }
    }
    
    printf("\n\n-CHECK TWO, MANUEL PLACEMENT-\n\n");
    
    Field my2Field;
    Field their2Field;
    FieldInit(&my2Field,&their2Field);
    
    printf("1) Init the fields\n");
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", my2Field.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", their2Field.grid[a][b]);
        }
    }
    
    printf("\n\n2) Manuel boat placement\n");
    
    printf(" -place huge boat east at 0,0\n");
    FieldAddBoat(&my2Field, 0, 0, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE);
    printf(" -place small boat south at 2,2\n");
    FieldAddBoat(&my2Field, 2, 2, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);
    printf(" -place large boat east at 2,2 (should return STANDARD_ERROR)\n");
    if (FieldAddBoat(&my2Field, 2, 2, FIELD_DIR_EAST, FIELD_BOAT_TYPE_HUGE) == STANDARD_ERROR) {printf("   -STANDARD ERROR RECIVED: existing boat overlap\n");}
    else{printf("   -TEST PASSED\n");}
    printf(" -place medium boat south at 5,5 (should return STANDARD_ERROR out of bounds)\n");
    if (FieldAddBoat(&my2Field, 5, 5, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM) == STANDARD_ERROR) {printf("   -STANDARD ERROR RECIVED: out of bounds\n");}
    else{printf("   -TEST PASSED\n");}
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", my2Field.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", their2Field.grid[a][b]);
        }
    }
    
    printf("\n\n2) Manuel boat attacks\n");
    
    printf(" -attack 0,0 (HUGE BOAT)\n");
    GuessData guess; guess.row = 0; guess.col = 0;
    int attack = FieldRegisterEnemyAttack(&my2Field,&guess);
    if (guess.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    printf(" -attack 0,1 (HUGE BOAT)\n");
    GuessData guess2; guess2.row = 0; guess2.col = 1;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess2);
    if (guess2.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    printf(" -attack 0,2 (HUGE BOAT)\n");
    GuessData guess3; guess3.row = 0; guess3.col = 2;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess3);
    if (guess3.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    printf(" -attack 0,3 (HUGE BOAT)\n");
    GuessData guess4; guess4.row = 0; guess4.col = 3;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess4);
    if (guess4.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    printf(" -attack 0,4 (HUGE BOAT)\n");
    GuessData guess5; guess5.row = 0; guess5.col = 4;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess5);
    if (guess5.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    printf(" -attack 0,5 (HUGE BOAT)\n");
    GuessData guess6; guess6.row = 0; guess6.col = 5;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess6);
    if (guess6.result == RESULT_HUGE_BOAT_SUNK){printf("   -HUGE BOAT SUNK\n");}
    else{printf("   -Attack missed\n");}
    int number = FieldGetBoatStates(&my2Field);
    printf("   -Ship Life bits: %d\n", number);
    printf(" -attack 1,1 (MISS)\n");
    GuessData guess7; guess7.row = 1; guess7.col = 1;
    attack = FieldRegisterEnemyAttack(&my2Field,&guess7);
    if (guess7.result == 1){printf("   -Attack hit\n");}
    else{printf("   -Attack missed\n");}
    
    printf("\n3) Update the board\n");
    
    FieldUpdateKnowledge(&my2Field,&guess);
    FieldUpdateKnowledge(&my2Field,&guess2);
    FieldUpdateKnowledge(&my2Field,&guess3);
    FieldUpdateKnowledge(&my2Field,&guess4);
    FieldUpdateKnowledge(&my2Field,&guess5);
    FieldUpdateKnowledge(&my2Field,&guess6);
    FieldUpdateKnowledge(&my2Field,&guess7);
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", my2Field.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", their2Field.grid[a][b]);
        }
    }
    
    printf("\n\n3) Changing individual squares\n");
    printf(" -place a medium boat piece at 3,3\n");
    FieldSetSquareStatus(&my2Field, 3, 5, FIELD_SQUARE_MEDIUM_BOAT);
    int num = FieldGetSquareStatus(&my2Field, 3, 5);
    printf(" -value at 3,3: %d\n", num);
    
    for(a=0;a<6;a++){
        printf("\n");
        for(b=0;b<10;b++){
            printf("%d ", my2Field.grid[a][b]);
        }
        printf("    ");
        for(b=0;b<10;b++){
            printf("%d ", their2Field.grid[a][b]);
        }
    }
    
   
}
