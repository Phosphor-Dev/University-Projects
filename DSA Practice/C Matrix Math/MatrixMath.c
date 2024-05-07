#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MatrixMath.h"
//prints matrix

void MatrixPrint(float mat[3][3]) {
    int i;
    int j;
    printf("\n");
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            printf("| %.2f ", mat[ i ][ j ]);
        }
        printf("|\n");
    }
    printf("\n");
}
//verifies if two matrices are equal

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    //check if all values at the same coordinates are equal to each other.
    int i;
    int j;
    int out = 1;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            if (mat1[i][j] != mat2[i][j]) {
                out = 0;
            }
        }
    }
    return out;
}
//adds two matrices together returns the sum

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    //adds the value in the first matrix to the value of the second matrix
    int i;
    int j;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

//multiplies two matrices together

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    //multiplies the value in the first matrix by the value in the second matrix
    int i;
    int j;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            result[i][j] = mat1[i][j] * mat2[i][j];
        }
    }
}
//adds a scalar to a matrix and returns the matrix

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]) {
    //add the constant to all individual values
    int i;
    int j;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            result[i][j] = mat[i][j] + x;
        }
    }
}
//multiplies the matrix by a scalar and returns it

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]) {
    //multiply all individual values by the constant
    int i, j;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            result[i][j] = mat[i][j] * x;
        }
    }
}
//returns the sum of the diagonal of the matrix

float MatrixTrace(float mat[3][3]) {
    //increment both x and y simultaneously and get the sum
    int k;
    float trace;
    for (k = 0; k != 3; k++) {
        trace = trace + mat[k][k];
    }
    return trace;
}
//transposes the matrix and returns it

void MatrixTranspose(float mat[3][3], float result[3][3]) {
    //for all values, swap x and y coord
    int i, j;
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            result[i][j] = mat[j][i];
        }
    }
}
//creates a 2x2 matrix given a 3x3 and a row and column to omit

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    //if the coordinate is not in the specified row or column, use it to fill the 2x2 matrix
    int k, l;
    int o = 0;
    for (k = 0; k != 3; k++) {
        for (l = 0; l != 3; l++) {
            if ((l != j) && (k != i)) {
                //pos1
                if (o == 0) {
                    result[0][0] = mat[k][l];
                }
                //pos2
                if (o == 1) {
                    result[0][1] = mat[k][l];
                }
                //pos3
                if (o == 2) {
                    result[1][0] = mat[k][l];
                }
                //pos4
                if (o == 3) {
                    result[1][1] = mat[k][l];
                }
                o++;
            }
        }
    }
    //printf("%ftl\n", result[0][0]);
    //printf("%ftr\n", result[0][1]);
    //printf("%fbl\n", result[1][0]);
    //printf("%fbr\n", result[1][1]);
}

//calculates the determinant
float MatrixDeterminant(float mat[3][3]) {
    float twox_matrix[2][2] = {
        {},
        {}
    };
    float sub1, sub2, sub3, det1, det2, det3, out;
    //calculates part 1 of determinant
    MatrixSubmatrix(0, 0, mat, twox_matrix);
    sub1 = ((twox_matrix[0][0] * twox_matrix[1][1]) - (twox_matrix[0][1] * twox_matrix[1][0]));
    det1 = mat[0][0] * sub1;
    //printf("%f1\n", sub1);
    
    //calculates part 2 of determinant
    MatrixSubmatrix(0, 1, mat, twox_matrix);
    sub2 = ((twox_matrix[0][0] * twox_matrix[1][1]) - (twox_matrix[0][1] * twox_matrix[1][0]));
    det2 = mat[0][1] * sub2;
    //printf("%f2\n", sub2);
    
    //calculates part 3 of determinant
    MatrixSubmatrix(0, 2, mat, twox_matrix);
    sub3 = ((twox_matrix[0][0] * twox_matrix[1][1]) - (twox_matrix[0][1] * twox_matrix[1][0]));
    det3 = mat[0][2] * sub3;
    //printf("%f3\n", det3);
    out = det1 - det2 + det3;
    return out;
}
//returns the inverse of the given matrix
void MatrixInverse(float mat[3][3], float result[3][3]) {
    float minor[3][3] = {
        {},
        {},
        {}
    };
    float cofactor[3][3] = {
        {},
        {},
        {}
    };
    float adjoint[3][3] = {
        {},
        {},
        {}
    };

    //calculates matrix of minors
    int i, j;
    float twox_matrix[2][2] = {
        {},
        {}
    };
    for (i = 0; i != 3; i++) {
        for (j = 0; j != 3; j++) {
            MatrixSubmatrix(i, j, mat, twox_matrix);
            minor[i][j] = ((twox_matrix[0][0] * twox_matrix[1][1]) - (twox_matrix[0][1] * twox_matrix[1][0]));
        }
    }

    //creates the matrix of cofactors
    cofactor[0][1] = (minor[0][1] * -1);
    cofactor[1][0] = (minor[1][0] * -1);
    cofactor[1][2] = (minor[1][2] * -1);
    cofactor[2][1] = (minor[2][1] * -1);
    cofactor[0][0] = minor[0][0];
    cofactor[0][2] = minor[0][2];
    cofactor[1][1] = minor[1][1];
    cofactor[2][0] = minor[2][0];
    cofactor[2][2] = minor[2][2];

    //creates the adjoint matrix
    MatrixTranspose(cofactor, adjoint);

    //multiplies entire matrix by 1/determinant of provided matrix
    float det = MatrixDeterminant(mat);
    det = 1 / det;
    MatrixScalarMultiply(det, adjoint, result);
}
