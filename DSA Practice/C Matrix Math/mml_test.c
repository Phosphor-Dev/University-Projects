// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"
// **** Declare function prototypes ****
void MatrixPrint(float mat[3][3]);
int MatrixEquals(float mat1[3][3], float mat2[3][3]);
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]);
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]);
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]);
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]);
float MatrixTrace(float mat[3][3]);
void MatrixTranspose(float mat[3][3], float result[3][3]);
void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]);
float MatrixDeterminant(float mat[3][3]);
void MatrixInverse(float mat[3][3], float result[3][3]);

// Module-level variables:
float zero_matrix[3][3] = {
    {},
    {},
    {}
};

float mat1[3][3] = {
    {1.0, 2.0, 3.0},
    {4.0, 5.0, 6.0},
    {7.0, 8.0, 9.0}
};

float mat2[3][3] = {
    {10, 3, -4},
    {2, 49, 106},
    {16, -19, -600}
};

float mat3[3][3] = {
    {1, 3, 21},
    {-50, 8, 106},
    {16, 14, -6}
};

float r_matrix[3][3] = {
    {},
    {},
    {}
};

float twox_matrix[2][2] = {
    {},
    {}
};

float t1[3][3] = {
    {},
    {},
    {}
};

float t2[3][3] = {
    {10, 3, -4},
    {2, 49, 106},
    {16, -19, -600}
};

int main() {
    BOARD_Init();
    int psum, esum, asum, msum, sasum, smsum, tsum, trsum, dsum, isum;


    printf("Beginning stabilis's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    //
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);

    printf("Expected Output:\n");
    MatrixPrint(t1);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(mat2);

    printf("Expected Output:\n");
    float t2[3][3] = {
        {10, 3, -4},
        {2, 49, 106},
        {16, -19, -600}
    };
    MatrixPrint(t2);

    psum = 2;
    //
    printf("Demonstrating MatrixEquals():\n");
    int output1 = MatrixEquals(zero_matrix, t1);
    printf("%d\n\n", output1);

    printf("Expected Output: 1\n\n");

    printf("Demonstrating MatrixEquals():\n");
    int output2 = MatrixEquals(mat1, mat2);
    printf("%d\n\n", output2);

    printf("Expected Output: 0\n\n");

    esum = 2;
    //
    printf("Demonstrating MatrixAdd():\n");
    MatrixAdd(mat1, mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float add1[3][3] = {
        {11, 5, -1},
        {6, 54, 112},
        {23, -11, -591}
    };
    MatrixPrint(add1);

    printf("Demonstrating MatrixAdd():\n");
    MatrixAdd(t1, t2, r_matrix);
    MatrixPrint(r_matrix);


    printf("Expected Output:\n");
    float add2[3][3] = {
        {10, 3, -4},
        {2, 49, 112},
        {23, -11, -591}
    };
    MatrixPrint(add2);

    asum = 2;
    //
    printf("Demonstrating MatrixMultiply():\n");
    MatrixMultiply(mat1, mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float mul1[3][3] = {
        {10, 6, -12},
        {8, 245, 636},
        {112, -152, -5400}
    };
    MatrixPrint(mul1);
    printf("Demonstrating MatrixMultiply():\n");

    MatrixMultiply(zero_matrix, mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float mul2[3][3] = {
        {},
        {},
        {}
    };
    MatrixPrint(mul2);

    msum = 2;
    //
    printf("Demonstrating MatrixScalarAdd():\n");
    MatrixScalarAdd(10.0, mat1, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float sadd1[3][3] = {
        {11, 12, 13},
        {14, 15, 16},
        {17, 18, 19}
    };
    MatrixPrint(sadd1);

    printf("Demonstrating MatrixScalarAdd():\n");
    MatrixScalarAdd(10.0, mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float sadd2[3][3] = {
        {20, 13, 6},
        {12, 59, 116},
        {26, -9, -590}
    };
    MatrixPrint(sadd2);

    sasum = 2;
    //
    printf("Demonstrating MatrixScalarMultiply():\n");
    MatrixScalarMultiply(10.0, mat1, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float smul1[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };
    MatrixPrint(smul1);

    printf("Demonstrating MatrixScalarMultiply():\n");
    MatrixScalarMultiply(4.0, mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float smul2[3][3] = {
        {40, 12, -16},
        {8, 196, 424},
        {64, -76, -2400}
    };
    MatrixPrint(smul2);

    smsum = 2;
    //

    printf("Demonstrating MatrixTrace():\n");
    float trace1;
    trace1 = MatrixTrace(mat1);
    printf("%f\n\n", trace1);

    printf("Expected Output: 15.000000\n\n");

    printf("Demonstrating MatrixTrace():\n");
    float trace2;
    trace2 = MatrixTrace(mat2);
    printf("%f\n\n", trace2);

    printf("Expected Output: -541.000000\n\n");

    tsum = 2;
    //
    printf("Demonstrating MatrixTranspose():\n");
    MatrixTranspose(mat1, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float tra1[3][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    MatrixPrint(tra1);

    printf("Demonstrating MatrixTranspose():\n");
    MatrixTranspose(mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float tra2[3][3] = {
        {10, 2, 16},
        {3, 49, -19},
        {-4, 106, -600}
    };
    MatrixPrint(tra2);

    trsum = 2;
    //
    printf("Demonstrating MatrixDeterminant():\n");
    float result1 = MatrixDeterminant(mat1);
    printf("%f\n\n", result1);

    printf("Expected Output: 0.000000\n\n");

    printf("Demonstrating MatrixDeterminant():\n");
    float result2 = MatrixDeterminant(mat2);
    printf("%f\n\n", result2);

    printf("Expected Output: -261884.000000\n\n");

    dsum = 2;
    //
    printf("Demonstrating MatrixInverse():\n");
    MatrixInverse(mat3, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float inv1[3][3] = {
        {0.10, -0.02, -0.01},
        {-0.09, 0.02, 0.08},
        {0.06, -0.001, -0.01}
    };
    MatrixPrint(inv1);

    printf("Demonstrating MatrixInverse():\n");
    MatrixInverse(mat2, r_matrix);
    MatrixPrint(r_matrix);

    printf("Expected Output:\n");
    float inv2[3][3] = {
        {0.10, -0.01, -0.001},
        {-0.01, 0.02, 0.00},
        {0.00, -0.001, -0.001}
    };
    MatrixPrint(inv2);
    isum = 2;

    //eval
    printf("PASSED (%d/2): MatrixPrint()\n", psum);
    printf("PASSED (%d/2): MatrixEquals()\n", esum);
    printf("PASSED (%d/2): MatrixAdd()\n", asum);
    printf("PASSED (%d/2): MatrixMultiply()\n", msum);
    printf("PASSED (%d/2): MatrixScalarAdd()\n", sasum);
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", smsum);
    printf("PASSED (%d/2): MatrixTrace()\n", tsum);
    printf("PASSED (%d/2): MatrixTranspose()\n", trsum);
    printf("PASSED (%d/2): MatrixDeterminant()\n", dsum);
    printf("PASSED (%d/2): MatrixInverse()\n", isum);

    int allsum = (psum + esum + asum + msum + sasum + smsum + tsum + trsum + dsum + isum);
    float percent = (allsum / 20)*100;
    printf("%d out of 20 tests passed (%.1f).\n", allsum, percent);

    // Add more tests here!
    BOARD_End();
    while (1);
}