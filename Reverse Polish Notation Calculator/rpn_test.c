// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main() {
    BOARD_Init();
    int error;
    printf("\n###### Beginning stabilis's rpn test harness: #####\n\n");

    //What follows is starter code.  You will need to modify it!
    int atests = 0, stests = 0, mtests = 0, dtests = 0, e1tests = 0,
            e2tests = 0, e3tests = 0, e4tests = 0, e5tests = 0, e6tests = 0;

    printf("Testing RPN_Evaluate\n\n");

    printf("Addition Input Test\n");
    char test1[] = "1 258 +";
    double result1;
    double expected1 = 259;
    printf("Input: %s \n", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("    Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("    Success!\n");
        atests++;
    }

    printf("Addition Input Test\n");
    char test2[] = "-4 -2 + 6 +";
    double result2;
    double expected2 = 0;
    printf("Input: %s \n", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result2 != expected2) {
        printf("    Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("    Success!\n");
        atests++;
    }

    printf("Subtraction Input Test\n");
    char test3[] = "7 5 -";
    double result3;
    double expected3 = 2;
    printf("Input: %s \n", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result3 != expected3) {
        printf("    Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("    Success!\n");
        stests++;
    }

    printf("Subtraction Input Test\n");
    char test4[] = "-5 6 - 5 +";
    double result4;
    double expected4 = -6;
    printf("Input: %s \n", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result4 != expected4) {
        printf("    Failed, expected = %f , result = %f\n", expected4, result4);
    } else {
        printf("    Success!\n");
        stests++;
    }

    printf("Multiplication Input Test\n");
    char test5[] = "5 5 *";
    double result5;
    double expected5 = 25;
    printf("Input: %s \n", test5);
    error = RPN_Evaluate(test5, &result5);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result5 != expected5) {
        printf("    Failed, expected = %f , result = %f\n", expected5, result5);
    } else {
        printf("    Success!\n");
        mtests++;
    }

    printf("Multiplication Input Test\n");
    char test6[] = "5 5 * -5 *";
    double result6;
    double expected6 = -125;
    printf("Input: %s \n", test6);
    error = RPN_Evaluate(test6, &result6);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result6 != expected6) {
        printf("    Failed, expected = %f , result = %f\n", expected6, result6);
    } else {
        printf("    Success!\n");
        mtests++;
    }

    printf("Division Input Test\n");
    char test7[] = "8 10 /";
    double result7;
    double expected7 = 0.8;
    printf("Input: %s \n", test7);
    error = RPN_Evaluate(test7, &result7);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result7 != expected7) {
        printf("    Failed, expected = %f , result = %f\n", expected7, result7);
    } else {
        printf("    Success!\n");
        dtests++;
    }

    printf("Division Input Test\n");
    char test8[] = "4 -2 / -1 /";
    double result8;
    double expected8 = 2;
    printf("Input: %s \n", test8);
    error = RPN_Evaluate(test8, &result8);
    if (error) {
        printf("    Failed, RPN_Evaluate produced an error\n");
    } else if (result8 != expected8) {
        printf("    Failed, expected = %f , result = %f\n", expected8, result8);
    } else {
        printf("    Success!\n");
        dtests++;
    }

    printf("\nError Testing\n");
    printf("Overflow Test\n");
    char test9[] = "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
    double result9;
    printf("Input: %s \n", test9);
    error = RPN_Evaluate(test9, &result9);
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("Proper error received. Success.\n\n");
        e1tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Overflow Test\n");
    char test10[] = "2 12312 5125 12 3 15 51 1 1 23 123 5 5 6 56 8 9 09 6 3 2 2 4 7"
    " 8 9 2 414 13 151";
    double result10;
    printf("Input: %s \n", test10);
    error = RPN_Evaluate(test10, &result10);
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("Proper error received. Success.\n\n");
        e1tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Underflow Test\n");
    char test11[] = "-";
    double result11;
    printf("Input: %s \n", test11);
    error = RPN_Evaluate(test11, &result11);
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("Proper error received. Success.\n\n");
        e2tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Underflow Test\n");
    char test12[] = "/";
    double result12;
    printf("Input: %s \n", test12);
    error = RPN_Evaluate(test12, &result12);
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("Proper error received. Success.\n\n");
        e2tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Invalid Token Test\n");
    char test13[] = "ajhb 1 +";
    double result13;
    printf("Input: %s \n", test13);
    error = RPN_Evaluate(test13, &result13);
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("Proper error received. Success.\n\n");
        e3tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Invalid Token Test\n");
    char test14[] = "/7 ";
    double result14;
    printf("Input: %s \n", test14);
    error = RPN_Evaluate(test14, &result14);
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("Proper error received. Success.\n\n");
        e3tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Divide By Zero Test\n");
    char test15[] = "1 0 /";
    double result15;
    printf("Input: %s \n", test15);
    error = RPN_Evaluate(test15, &result15);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("Proper error received. Success.\n\n");
        e4tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Divide By Zero Test\n");
    char test16[] = "810 5 + 0 /";
    double result16;
    printf("Input: %s \n", test16);
    error = RPN_Evaluate(test16, &result16);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("Proper error received. Success.\n\n");
        e4tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Too Few Items Remain Test\n");
    char test17[] = "7 +";
    double result17;
    printf("Input: %s \n", test17);
    error = RPN_Evaluate(test17, &result17);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("Proper error received. Success.\n\n");
        e5tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Too Few Items Remain Test\n");
    char test18[] = "32 -";
    double result18;
    printf("Input: %s \n", test18);
    error = RPN_Evaluate(test18, &result18);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("Proper error received. Success.\n\n");
        e5tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Too Many Items Remain Test\n");
    char test19[] = " 4 4 4 4 +";
    double result19;
    printf("Input: %s \n", test19);
    error = RPN_Evaluate(test19, &result19);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("Proper error received. Success.\n\n");
        e6tests++;
    } else {
        printf("Failed.");
    }
    
    printf("Too Many Items Remain Test\n");
    char test20[] = "6 19 23 9 + -";
    double result20;
    printf("Input: %s \n", test20);
    error = RPN_Evaluate(test20, &result20);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("Proper error received. Success.\n\n");
        e6tests++;
    } else {
        printf("Failed.");
    }

    printf("\nResults:\n");
    printf("Addition: %d/2 Passed\n", atests);
    printf("Subtraction: %d/2 Passed\n", stests);
    printf("Multiplication: %d/2 Passed\n", mtests);
    printf("Division: %d/2 Passed\n", dtests);
    printf("Overflow: %d/2 Passed\n", e1tests);
    printf("Underflow: %d/2 Passed\n", e2tests);
    printf("Invalid Token: %d/2 Passed\n", e3tests);
    printf("Divide By Zero: %d/2 Passed\n", e4tests);
    printf("Too Few Items: %d/2 Passed\n", e5tests);
    printf("Too Many Items: %d/2 Passed\n", e6tests);
    
    
    /*
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "1233\b4";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");
     */

    BOARD_End();
    while (1);
}


