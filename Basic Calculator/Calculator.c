// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"




// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
double Subtract(double operand1, double operand2);
double Divide(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Round(double operand);

void CalculatorRun(void) {
    //program open message
    printf("\n\nWelcome to Steven's calculator program! Compiled at %s %s\n\n", __DATE__, __TIME__);
    //inf loop
    while (1) {
        //declare op var
        char op;
        //declare all possible operand vars
        double operand, operand1, operand2;
        //prompt and call for op var
        printf("Enter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,r): ");
        scanf(" %c", &op);
        //end prog if receive character q
        if (op == 'q') {
            return;
        }
        //if op not false or zero
        if (op) {
            //branch for all unary functions
            if ((op == 'a') || (op == 'c') || (op == 'f') || (op == 't') || (op == 'r')) {
                //prompt and call for first operand
                printf("    Enter the first operand: ");
                scanf(" %lf", &operand);
                //branch for absolute value
                if (op == 'a') {
                    double out = AbsoluteValue(operand);
                    printf("    Result of |%lf|: %lf\n", operand, out);
                    //branch for F to C
                } else if (op == 'c') {
                    double out = FahrenheitToCelsius(operand);
                    printf("    Result of (%lf deg->C): %lf\n", operand, out);
                    //branch for C to F
                } else if (op == 'f') {
                    double out = CelsiusToFahrenheit(operand);
                    printf("    Result of (%lf deg->F): %lf\n", operand, out);
                    //branch for tangent
                } else if (op == 't') {
                    double out = Tangent(operand);
                    printf("    Result of tan(%lf): %lf\n", operand, out);
                    //branch for round
                } else if (op == 'r') {
                    double out = Round(operand);
                    printf("    Result of round(%lf): %lf\n", operand, out);
                }
                //branch for all binary functions
            } else if ((op == '*') || (op == '/') || (op == '+') || (op == '-') || (op == 'm')) {
                //prompt and call for operand 1
                printf("    Enter the first operand: ");
                scanf(" %lf", &operand1);
                //prompt and call for operand2
                printf("    Enter the second operand: ");
                scanf(" %lf", &operand2);
                //branch for addition
                if (op == '+') {
                    double out = Add(operand1, operand2);
                    printf("    Result of (%lf + %lf): %lf\n", operand1, operand2, out);
                    //branch for subtraction
                } else if (op == '-') {
                    double out = Subtract(operand1, operand2);
                    printf("    Result of (%lf - %lf): %lf\n", operand1, operand2, out);
                    //branch for multiply
                } else if (op == '*') {
                    double out = Multiply(operand1, operand2);
                    printf("    Result of (%lf * %lf): %lf\n", operand1, operand2, out);
                    //branch for divide
                } else if (op == '/') {
                    double out = Divide(operand1, operand2);
                    if (out == HUGE_VAL) {
                        printf("    Divide by zero error!");
                    } else {
                        printf("    Result of (%lf / %lf): %lf\n", operand1, operand2, out);
                    }
                    //branch for average
                } else if (op == 'm') {
                    double out = Average(operand1, operand2);
                    printf("    Result of average(%lf, %lf): %lf\n", operand1, operand2, out);
                }
                //branch for non valid input
            } else {
                printf("Error, not a valid operator\n");
            }
        }
        //newline at the end of prog
        printf("\n");
    }
}
/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
//Addition sub function. Takes two given inputs and adds them together, returns value

double Add(double operand1, double operand2) {
    double result = operand1 + operand2;
    return result;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
//Subtraction sub function. Takes two given inputs, subtracts them, and then returns value

double Subtract(double operand1, double operand2) {
    double result = operand1 - operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
//Multiplication sub function Takes two given inputs, multiplies them, returns the value

double Multiply(double operand1, double operand2) {
    double result = operand1 * operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
//Division subfunction. Takes in two numbers and divides the first by the second. Returns the value.

double Divide(double operand1, double operand2) {
    // branch if attempting to divide by zero, returning HUGE_VAL if that is the case
    if (operand2 == 0) {
        return HUGE_VAL;
    } else {
        double result = operand1 / operand2;
        return result;
    }
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
//Takes in a value and returns its absolute value

double AbsoluteValue(double operand) {
    if (operand < 0) {
        double result = operand * (-1);
        return result;
    } else {
        return operand;
    }
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
//F to C sub function. Takes in a Fahrenheit value and converts it to Celsius. Returns it.

double FahrenheitToCelsius(double operand) {
    double result = (5.0 / 9.0)*(operand - 32.0);
    return result;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
//C to F sub function. Takes in a Celsius value and converts it to Fahrenheit. Returns it.

double CelsiusToFahrenheit(double operand) {
    double result = (((9.0 / 5.0) * operand) + 32.0);
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
//average sub function. Takes in two numbers, returns the average of both.

double Average(double operand1, double operand2) {
    //add both values
    double temp = operand1 + operand2;
    //divides by two
    double result = temp / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
//Tangent sub function. Takes a value in degrees, converts to radians, outputs the tangent of the angle.

double Tangent(double operand) {
    //convert to rad
    double rad = (operand * (M_PI / 180));
    double result = tan(rad);
    return result;
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
//Round sub function. Rounds the given value up or down and then returns it.

double Round(double operand) {
    if (operand < 0) {
        //equivalent to the floor function
        double temp = (int) operand;
        //gets only the decimal part of the value
        double qual = operand - temp;
        //rounds up or down based on the decimal
        if (qual <= -0.5) {
            temp = temp - 1;
            return temp;
        } else {
            return temp;
        }

    } else {
        //equivalent to the floor function
        double temp = (int) operand;
        //gets only the decimal part of the value
        double qual = operand - temp;
        //rounds up or down based on the decimal
        if (qual >= 0.5) {
            temp = temp + 1;
            return temp;
        } else {
            return temp;
        }
    }
}
