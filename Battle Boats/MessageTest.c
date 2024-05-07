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
#include "Negotiation.h"
#include "Field.h"
#include "Message.h"

#include <stdio.h>
#include <stdlib.h>

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
    printf("\n\nWelcome to Steven's program! Compiled at %s %s\n\n", __DATE__, __TIME__);
    printf("Testing Message_CalculateChecksum() and Message_ParseMessage()\n\n");
    printf("Passing payload: CHA,45745\n");
    int error1 = 0;
    BB_Event parsed = {.type = BB_EVENT_NO_EVENT,
        .param0 = 0,
        .param1 = 0,
        .param2 = 0};
    uint8_t checksum;
    const char* payload1;
    payload1 = "CHA,45745";
    checksum = Message_CalculateChecksum(payload1);
    printf("Checksum should be: 51\n");
    printf("Received: %X\n\n", checksum);

    printf("Creating BB_Event...\n");
    error1 = Message_ParseMessage(payload1, "51", &parsed);
    printf("BB_Event contains the following data:\n");
    if (error1 != STANDARD_ERROR) {
        printf("type: BB_EVENT_CHA_RECEIVED\n");
        printf("param0: %d\n", parsed.param0);
        printf("param1: %d\n", parsed.param1);
        printf("param2: %d\n\n", parsed.param2);
    } else {
        printf("Produced an ERROR return.\n\n");
    }

    //--------------------------------------------------------------------------
    printf("Passing payload: SHO,5,7\n");
    BB_Event parsed2 = {.type = BB_EVENT_NO_EVENT,
        .param0 = 0,
        .param1 = 0,
        .param2 = 0};
    uint8_t checksum2;
    const char* payload2;
    payload2 = "SHO,5,7";
    checksum2 = Message_CalculateChecksum(payload2);
    printf("Checksum should be: 56\n");
    printf("Received: %X\n\n", checksum2);

    printf("Creating BB_Event...\n");
    error1 = Message_ParseMessage(payload2, "56", &parsed2);
    printf("BB_Event contains the following data:\n");
    if (error1 != STANDARD_ERROR) {
        printf("type: BB_EVENT_SHO_RECEIVED\n");
        printf("param0: %d\n", parsed2.param0);
        printf("param1: %d\n", parsed2.param1);
        printf("param2: %d\n\n", parsed2.param2);
    } else {
        printf("Produced an ERROR return.\n\n");
    }

    //--------------------------------------------------------------------------

    printf("Passing payload: RES,1,5,1\n");
    BB_Event parsed3 = {.type = BB_EVENT_NO_EVENT,
        .param0 = 0,
        .param1 = 0,
        .param2 = 0};
    uint8_t checksum3;
    const char* payload3;
    payload3 = "RES,1,5,1";
    checksum3 = Message_CalculateChecksum(payload3);
    printf("Checksum should be: 5D\n");
    printf("Received: %X\n\n", checksum3);

    printf("Creating BB_Event...\n");
    error1 = Message_ParseMessage(payload3, "5D", &parsed3);
    printf("BB_Event contains the following data:\n");
    if (error1 != STANDARD_ERROR) {
        printf("type: BB_EVENT_RES_RECEIVED\n");
        printf("param0: %d\n", parsed3.param0);
        printf("param1: %d\n", parsed3.param1);
        printf("param2: %d\n\n", parsed3.param2);
    } else {
        printf("Produced an ERROR return.\n\n");
    }

    //--------------------------------------------------------------------------

    printf("Testing Message_Encode()\n\n");
    printf("Passing Items: RES,1,5,1\n");
    char message1[MESSAGE_MAX_PAYLOAD_LEN];
    Message encoded1;
    encoded1.type = MESSAGE_RES;
    encoded1.param0 = 1;
    encoded1.param1 = 5;
    encoded1.param2 = 1;
    int messageLen1 = Message_Encode(message1, encoded1);
    printf("Encoded Return: %s\n", message1);
    printf("Encoded Return Length: %d\n\n", messageLen1);

    //--------------------------------------------------------------------------

    printf("Passing Items: SHO,5,7\n");
    char message2[MESSAGE_MAX_PAYLOAD_LEN];
    Message encoded2;
    encoded2.type = MESSAGE_SHO;
    encoded2.param0 = 5;
    encoded2.param1 = 7;
    encoded2.param2 = 0;
    int messageLen2 = Message_Encode(message2, encoded2);
    printf("Encoded Return: %s\n", message2);
    printf("Encoded Return Length: %d\n\n", messageLen2);

    //--------------------------------------------------------------------------

    printf("Passing Items: CHA,45745\n");
    char message3[MESSAGE_MAX_PAYLOAD_LEN];
    Message encoded3;
    encoded3.type = MESSAGE_CHA;
    encoded3.param0 = 45745;
    encoded3.param1 = 0;
    encoded3.param2 = 0;
    int messageLen3 = Message_Encode(message3, encoded3);
    printf("Encoded Return: %s\n", message3);
    printf("Encoded Return Length: %d\n\n", messageLen3);

    //--------------------------------------------------------------------------

    printf("Testing Message_Decode()\n\n");
    printf("Passing Item: $RES,1,0,3*5A\\n\n");

    char char1[MESSAGE_MAX_LEN] = "$RES,1,0,3*5A\n";
    int i = 0, errors1 = 0;
    BB_Event decoded1;
    while (char1[i] != '\n') {
        Message_Decode(char1[i], &decoded1);
        i++;

    }
    errors1 = Message_Decode('\n', &decoded1);

    if (errors1 == SUCCESS) {
        printf("Success.\n\n");
    } else {
        printf("Failed.\n\n");
    }
    
    
    
    printf("Passing Item: $CHA,43182*5A\\n\n");

    char char2[MESSAGE_MAX_LEN] = "$CHA,43182*5A\n";
    int j = 0, errors2 = 0;
    BB_Event decoded2;
    while (char2[j] != '\n') {
        Message_Decode(char2[j], &decoded2);
        j++;

    }
    errors2 = Message_Decode('\n', &decoded2);

    if (errors2 == SUCCESS) {
        printf("Success.\n\n");
    } else {
        printf("Failed.\n\n");
    }
    
    
    printf("Passing Item: $SHO,4,8*58\\n\n");

    char char3[MESSAGE_MAX_LEN] = "$SHO,4,8*58\n";
    int k = 0, errors3 = 0;
    BB_Event decoded3;
    while (char3[k] != '\n') {
        Message_Decode(char3[k], &decoded3);
        k++;

    }
    errors3 = Message_Decode('\n', &decoded3);

    if (errors3 == SUCCESS) {
        printf("Success.\n\n");
    } else {
        printf("Failed.\n\n");
    }
    
    

    while (TRUE);
}