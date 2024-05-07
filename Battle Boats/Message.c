// **** Include libraries here ****
// Standard libraries
#include <ctype.h> 
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

typedef enum {
    WAITING_FOR_DELIMITER,
    RECORDING_PAYLOAD,
    RECORDING_CHECKSUM,
} DecodeState;

//needed for the decode
static int decodeState = WAITING_FOR_DELIMITER;
static char receivedPayload[MESSAGE_MAX_PAYLOAD_LEN];
static char receivedChecksum[MESSAGE_CHECKSUM_LEN];

/**
 * Given a payload string, calculate its checksum
 * 
 * @param payload       //the string whose checksum we wish to calculate
 * @return   //The resulting 8-bit checksum 
 */


uint8_t Message_CalculateChecksum(const char* payload) {
    int i = 0;
    //clear checksum
    uint8_t checksum = 0x00;
    //loop until no char
    while (payload[i] != '\0') {
        //xor with next char
        checksum = checksum ^(int) payload[i];
        i++;
    }
    return (checksum);
}

/**
 * ParseMessage() converts a message string into a BB_Event.  The payload and
 * checksum of a message are passed into ParseMessage(), and it modifies a
 * BB_Event struct in place to reflect the contents of the message.
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //A BB_Event which will be modified by this function.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              the payload does not match the checksum
 *              the checksum string is not two characters long
 *              the message does not match any message template
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */
int Message_ParseMessage(const char* payload,
        const char* checksum_string, BB_Event * message_event) {
    //max payload error
    if (strlen(payload) > MESSAGE_MAX_PAYLOAD_LEN) {
        message_event->type = BB_EVENT_ERROR;
        printf("Error1\n");
        return (STANDARD_ERROR);
    }

    //incorrect checksum format
    uint8_t checksum = Message_CalculateChecksum(payload);
    printf("FUNCTIONCHEKCKSUM: %X", checksum);
    if (strlen(checksum_string) != MESSAGE_CHECKSUM_LEN) {
        message_event->type = BB_EVENT_ERROR;
        printf("Error2\n");
        return (STANDARD_ERROR);
    }

    //incorrect checksum format
    char actualChecksum[100];
    sprintf(&actualChecksum[0], "%X", checksum);
    int v = 0;
    while ((checksum_string[v] != '\0') && (actualChecksum[v] != '\0')) {
        if ((checksum_string[v]) != (actualChecksum[v])) {
            message_event->type = BB_EVENT_ERROR;
            printf("CHECKSTRING: %s\n", checksum_string);
            printf("ACTUALSTRING: %s\n", actualChecksum);
            printf("CHECKSTRING: %c\n", checksum_string[v]);
            printf("ACTUALSTRING: %c\n", actualChecksum[v]);
            printf("Error3\n");
            return (STANDARD_ERROR);
        }
        v++;
    }

    //init all variable for tokenization and param storing
    char payloadTemp[MESSAGE_MAX_PAYLOAD_LEN];
    char *currentToken = "";
    char *tokenExtract;
    char *tokenExtract1;
    char *tokenExtract2;

    uint16_t param0;
    uint16_t param1;
    uint16_t param2;

    //loop first three chars for event text and store
    strcpy(payloadTemp, payload);
    int i = 0;
    int typeCounter = 0;
    char type[MESSAGE_MAX_PAYLOAD_LEN];
    while (i < 3) {
        type[typeCounter] = payload[i];
        typeCounter++;
        i++;
    }
    type[typeCounter] = 0;
    type[strlen(type)] = '\0';

    //fill rest of array with \0
    int j = i;
    for (j = i; j < MESSAGE_MAX_PAYLOAD_LEN; j++) {
        type[j] = '\0';
    }

    //check if valid message starter
    if ((strcmp(type, "CHA") != 0)
            && (strcmp(type, "ACC") != 0)
            && (strcmp(type, "REV") != 0)
            && (strcmp(type, "SHO") != 0)
            && (strcmp(type, "RES") != 0)) {

        message_event->type = BB_EVENT_ERROR;
        printf("Error4\n");
        return (STANDARD_ERROR);
    }

    //challenge
    if (strcmp(type, "CHA") == 0) {
        message_event->type = BB_EVENT_CHA_RECEIVED;
        currentToken = strtok(payloadTemp, ",");
        tokenExtract = strtok(NULL, ",");
        if ((strcmp("0", tokenExtract) != 0) && (atoi(tokenExtract) == 0)) {
            printf("Error5\n");
            return STANDARD_ERROR;
        }
        param0 = (uint16_t) atoi(tokenExtract);
        message_event->param0 = param0;
        return SUCCESS;

        //accepted
    } else if (strcmp(type, "ACC") == 0) {
        message_event->type = BB_EVENT_ACC_RECEIVED;
        currentToken = strtok(payloadTemp, ",");
        tokenExtract = strtok(NULL, ",");
        if (strcmp("0", tokenExtract) != 0 && atoi(tokenExtract) == 0) {
            printf("Error6\n");
            return STANDARD_ERROR;
        }
        param0 = (uint16_t) atoi(tokenExtract);
        message_event->param0 = param0;
        return SUCCESS;

        //reveal hash
    } else if (strcmp(type, "REV") == 0) {
        message_event->type = BB_EVENT_REV_RECEIVED;
        currentToken = strtok(payloadTemp, ",");
        tokenExtract = strtok(NULL, ",");
        if (strcmp("0", tokenExtract) != 0 && atoi(tokenExtract) == 0) {
            printf("Error7\n");
            return STANDARD_ERROR;
        }
        param0 = (uint16_t) atoi(tokenExtract);
        message_event->param0 = param0;
        return SUCCESS;

        //shot fired
    } else if (strcmp(type, "SHO") == 0) {
        message_event->type = BB_EVENT_SHO_RECEIVED;
        currentToken = strtok(payloadTemp, ",");
        tokenExtract = strtok(NULL, ",");
        if (strcmp("0", tokenExtract) != 0 && atoi(tokenExtract) == 0) {
            printf("Error8\n");
            return STANDARD_ERROR;
        }
        param0 = (uint16_t) atoi(tokenExtract);
        message_event->param0 = param0;
        tokenExtract1 = strtok(NULL, ",");
        if (strcmp("0", tokenExtract1) != 0 && atoi(tokenExtract1) == 0) {
            printf("Error9\n");
            return STANDARD_ERROR;
        }
        param1 = (uint16_t) atoi(tokenExtract1);
        message_event->param1 = param1;

        return SUCCESS;

        //respond to fired shot
    } else if (strcmp(type, "RES") == 0) {
        message_event->type = BB_EVENT_RES_RECEIVED;
        currentToken = strtok(payloadTemp, ",");
        printf("1: %s\n", currentToken);
        tokenExtract = strtok(NULL, ",");
        printf("2: %s\n", tokenExtract);
        if (strcmp("0", tokenExtract) != 0 && atoi(tokenExtract) == 0) {
            printf("Error11\n");
            return STANDARD_ERROR;
        }
        param0 = (uint16_t) atoi(tokenExtract);
        message_event->param0 = param0;
        tokenExtract1 = strtok(NULL, ",");
        printf("3: %s\n", tokenExtract1);
        if (strcmp("0", tokenExtract1) != 0 && atoi(tokenExtract1) == 0) {
            printf("Error12\n");
            return STANDARD_ERROR;
        }
        param1 = (uint16_t) atoi(tokenExtract1);
        message_event->param1 = param1;
        tokenExtract2 = strtok(NULL, ",");
        printf("4: %s\n", tokenExtract2);
        if (strcmp("0", tokenExtract2) != 0 && atoi(tokenExtract2) == 0) {
            printf("Error13\n");
            return STANDARD_ERROR;
        }
        param2 = (uint16_t) atoi(tokenExtract2);
        message_event->param2 = param2;

        return SUCCESS;
    }
    char *tra = "";
    sprintf(tra, "%s", currentToken);
    return (SUCCESS);
}

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_*,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode) {
    uint8_t checksum;
    switch (message_to_encode.type) {
        case MESSAGE_NONE:
            return 0;
            break;
        case MESSAGE_CHA:
            sprintf(message_string, "CHA,%u",
                    message_to_encode.param0);
            checksum = Message_CalculateChecksum(message_string);
            sprintf(message_string, "$CHA,%u*%X\n",
                    message_to_encode.param0,
                    checksum);
            break;
        case MESSAGE_ACC:
            sprintf(message_string, "ACC,%u",
                    message_to_encode.param0);
            checksum = Message_CalculateChecksum(message_string);
            sprintf(message_string, "$ACC,%u*%X\n",
                    message_to_encode.param0,
                    checksum);
            break;
        case MESSAGE_REV:
            sprintf(message_string, "REV,%u",
                    message_to_encode.param0);
            checksum = Message_CalculateChecksum(message_string);
            sprintf(message_string, "$REV,%u*%X\n",
                    message_to_encode.param0,
                    checksum);
            break;
        case MESSAGE_SHO:
            sprintf(message_string, "SHO,%d,%d",
                    message_to_encode.param0,
                    message_to_encode.param1);
            checksum = Message_CalculateChecksum(message_string);
            sprintf(message_string, "$SHO,%d,%d*%X\n",
                    message_to_encode.param0,
                    message_to_encode.param1,
                    checksum);
            break;
        case MESSAGE_RES:
            sprintf(message_string, "RES,%u,%u,%u",
                    message_to_encode.param0,
                    message_to_encode.param1,
                    message_to_encode.param2);
            checksum = Message_CalculateChecksum(message_string);
            sprintf(message_string, "$RES,%u,%u,%u*%X\n",
                    message_to_encode.param0,
                    message_to_encode.param1,
                    message_to_encode.param2,
                    checksum);
            break;
        case MESSAGE_ERROR:
            return 0;
    }
    return strlen(message_string);
}

/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                          if char_in is the last character of an invalid message,
 *                              then decoded_message should have an ERROR type.
 *                          otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */



int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) {
    static int payloadLen = 0;
    static int checksumLen = 0;

    switch (decodeState) {
        case WAITING_FOR_DELIMITER:
            //clear all variables and prepare for new data
            if (char_in == '$') {
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                decodeState = RECORDING_PAYLOAD;
                payloadLen = 0;
                checksumLen = 0;
                receivedPayload[payloadLen] = 0;
                receivedChecksum[checksumLen] = 0;
            }
            break;

        case RECORDING_PAYLOAD:
            printf("CHARIN: %c\n", char_in);
            decoded_message_event->type = BB_EVENT_NO_EVENT;
            //next state
            if (char_in == '*') {
                decodeState = RECORDING_CHECKSUM;
                break;
                //error breaks
            } else if (payloadLen > MESSAGE_MAX_PAYLOAD_LEN) {
                printf("HEERE1\n\n");
                decodeState = WAITING_FOR_DELIMITER;
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                return (STANDARD_ERROR);
            } else if ((char_in == '$') || (char_in == '\n')) {

                printf("HEERE2\n\n");
                decodeState = WAITING_FOR_DELIMITER;
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                return (STANDARD_ERROR);
            } else {
                //increment all counters and store char received
                receivedPayload[payloadLen] = char_in;
                printf("ENTIRE PAYLOAD: %s\n", receivedPayload);
                payloadLen++;
                receivedPayload[payloadLen] = 0;
                break;
            }

        case RECORDING_CHECKSUM:
            //check if char is hex
            if ((!(isxdigit(char_in)) && (char_in != '\n'))) {
                decodeState = WAITING_FOR_DELIMITER;
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                return (STANDARD_ERROR);
                break;
                //check for message end
            } else if (char_in == '\n') {
                if ((checksumLen) != MESSAGE_CHECKSUM_LEN) {
                    decodeState = WAITING_FOR_DELIMITER;
                    decoded_message_event->type = BB_EVENT_NO_EVENT;
                    return (STANDARD_ERROR);
                    break;
                }
                //parse received checksum and message
                int parseResult = Message_ParseMessage(
                        receivedPayload,
                        receivedChecksum,
                        decoded_message_event);
                printf("PAYLOADDD: %s\n", receivedPayload);
                printf("CHECKSUMM: %s\n", receivedChecksum);
                //error return if error
                if (parseResult != STANDARD_ERROR) {
                    decodeState = WAITING_FOR_DELIMITER;
                    return (SUCCESS);
                    break;
                } else {
                    decodeState = WAITING_FOR_DELIMITER;
                    decoded_message_event->type = BB_EVENT_NO_EVENT;
                    return (STANDARD_ERROR);
                    break;
                }
                break;
            } else {
                //increment all counters and store char
                receivedChecksum[checksumLen] = char_in;
                checksumLen++;
                receivedChecksum[checksumLen] = 0;

            }
    }
    return SUCCESS;
}
