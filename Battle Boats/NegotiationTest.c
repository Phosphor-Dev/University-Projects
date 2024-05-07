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



int main() {
    BOARD_Init();
    TRISE = 0;
    LATE = 0;
    //initialize CE13 libraries:
    //ButtonsInit();
    OledInit();
    //Print a greeting:
    printf("\n\nWelcome to Steven's program! Compiled at %s %s\n\n", __DATE__, __TIME__);
    OledUpdate();
    
    printf("Testing NegotiationHash()\n\n");
    printf("Passing NegotiationData secret value of: 0x1F3A\n");
    
    NegotiationData secret = 0x1F3A;
    NegotiationData returnedHash;
    returnedHash  = NegotiationHash(secret);
    printf("Calculated Hash Value: 0x%x\n", returnedHash);
    printf("Hash should be: 0x4aef\n\n");
    
    printf("Passing NegotiationData secret value of: 0xE413\n");
    
    secret = 0xE413;
    returnedHash  = NegotiationHash(secret);
    printf("Calculated Hash Value: 0x%x\n", returnedHash);
    printf("Hash should be: 0x59dd\n\n");
    
    printf("Passing NegotiationData secret value of: 0x0000\n");
    
    secret = 0x0000;
    returnedHash  = NegotiationHash(secret);
    printf("Calculated Hash Value: 0x%x\n", returnedHash);
    printf("Hash should be: 0x0000\n\n");
    
    
    printf("Testing NegotiationVerify()\n\n");
    printf("Passing NegotiationData secret value of: 0x1F3A\n");        
    printf("Passing NegotiationData commitment value of: 0x4aef\n"); 
    
    secret = 0x1F3A;
    NegotiationData commitment = 0x4aef;
    int returnedVerify;
    returnedVerify = NegotiationVerify(secret, commitment);
    if (returnedVerify == TRUE){
        printf("Success.\n\n");
    } else {
        printf("Fail.\n\n");
    }
    
    printf("Passing NegotiationData secret value of: 0xE413\n");        
    printf("Passing NegotiationData commitment value of: 0x59dd\n"); 
    
    secret = 0xE413;
    commitment = 0x59dd;
    returnedVerify = NegotiationVerify(secret, commitment);
    if (returnedVerify == TRUE){
        printf("Success.\n\n");
    } else {
        printf("Fail.\n\n");
    }
    
    printf("Passing NegotiationData secret value of: 0x0000\n");        
    printf("Passing NegotiationData commitment value of: 0x0000\n"); 
    
    secret = 0x0000;
    commitment = 0x0000;
    returnedVerify = NegotiationVerify(secret, commitment);
    if (returnedVerify == TRUE){
        printf("Success.\n\n");
    } else {
        printf("Fail.\n\n");
    }
    
    
    printf("Testing NegotiationCoinFlip()\n\n");
    printf("Passing NegotiationData A secret value of: 0x1F3A\n");
    printf("Passing NegotiationData B secret value of: 0xE413\n");
    //0x1F3a
    NegotiationData secretA = 0x1F3A;
    NegotiationData secretB = 0xE413;
    NegotiationOutcome outcome;
    outcome = NegotiateCoinFlip(secretA, secretB);
    if (outcome == HEADS) {
        printf("Coin Flip Result: HEADS\n");
    } else {
        printf("Coin Flip Result: TAILS\n");
    }
    printf("Result should be: TAILS\n\n");
    
    printf("Passing NegotiationData A secret value of: 0x1F3B\n");
    printf("Passing NegotiationData B secret value of: 0xE413\n");
    //0x1F3a
    secretA = 0x1F3B;
    secretB = 0xE413;
    outcome = NegotiateCoinFlip(secretA, secretB);
    if (outcome == HEADS) {
        printf("Coin Flip Result: HEADS\n");
    } else {
        printf("Coin Flip Result: TAILS\n");
    }
    printf("Result should be: HEADS\n\n");
    
    printf("Passing NegotiationData A secret value of: 0x0000\n");
    printf("Passing NegotiationData B secret value of: 0x0000\n");
    //0x1F3a
    secretA = 0x0000;
    secretB = 0x0000;
    outcome = NegotiateCoinFlip(secretA, secretB);
    if (outcome == HEADS) {
        printf("Coin Flip Result: HEADS\n");
    } else {
        printf("Coin Flip Result: TAILS\n");
    }
    printf("Result should be: TAILS\n\n");
    
    while (1);
}

