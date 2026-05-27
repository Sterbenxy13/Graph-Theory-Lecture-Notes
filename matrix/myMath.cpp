
#include <iostream>

#include "MyMatrix.h"

MyMatrix mySumMatrices(MyMatrix A, MyMatrix B) {
    MyMatrix result = MyMatrix(A.lines, A.columns);

    for (int i = 0; i < A.lines; i++) {
        for (int j = 0; j < A.columns; j++) {
            result.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
        }
    }

    return result;
}

MyMatrix myMultiplyMatrices(MyMatrix A, MyMatrix B) {
    MyMatrix result = MyMatrix(A.lines, B.columns);

    for (int i = 0; i < A.lines; i++) {
        for (int j = 0; j < B.columns; j++) {
            for (int k = 0; k < (A.columns); k++) {
                result.matrix[i][j] = result.matrix[i][j] + A.matrix[i][k] * B.matrix[k][j];
            }
        }
    }

    return result;
}











