
#include <iostream>

#include "myMath.h"

#define A_SIZE 4
#define B_SIZE 5

int** getMatrixB() {
    int** matrix = new int*[B_SIZE];
    for (int i = 0; i < B_SIZE; i++) {
        matrix[i] = new int[B_SIZE];
    }

    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 0;
    matrix[0][3] = 1;
    matrix[0][4] = 0;

    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 0;
    matrix[1][3] = 2;
    matrix[1][4] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 0;
    matrix[2][4] = 2;

    matrix[3][0] = 1;
    matrix[3][1] = 2;
    matrix[3][2] = 0;
    matrix[3][3] = 0;
    matrix[3][4] = 0;

    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 2;
    matrix[4][3] = 0;
    matrix[4][4] = 1;

    return matrix;
}

int** getMatrixA() {
    int** matrix = new int*[A_SIZE];
    for (int i = 0; i < A_SIZE; i++) {
        matrix[i] = new int[A_SIZE];
    }

    matrix[0][0] = 0;
    matrix[0][1] = 0;
    matrix[0][2] = 2;
    matrix[0][3] = 1;

    matrix[1][0] = 0;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[1][3] = 0;

    matrix[2][0] = 2;
    matrix[2][1] = 1;
    matrix[2][2] = 0;
    matrix[2][3] = 0;

    matrix[3][0] = 1;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 0;

    return matrix;
}

void printMatrix(MyMatrix matrix) {
    std::cout << "   | ";
    for (int i = 0; i < matrix.lines; i++) {
        std::cout << 'p' << i + 1 << " | ";
    }
    std::cout << std::endl;

    for (int i = 0; i < matrix.lines; i++) {
        std::cout << 'p' << i + 1 << " | ";
        for (int j = 0; j < matrix.columns; j++) {
            std::cout << matrix.matrix[i][j] << "  | ";
        }
        std::cout << std::endl;
    }
}

#define TESTE_SIZE 5
int** getMatrixTeste() {
    
    int** matrix = new int*[TESTE_SIZE];
    for (int i = 0; i < TESTE_SIZE; i++) {
        matrix[i] = new int[TESTE_SIZE];
    }

    matrix[0][0] = 0;
    matrix[0][1] = 1;
    matrix[0][2] = 0;
    matrix[0][3] = 0;
    matrix[0][4] = 0;

    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[1][3] = 1;
    matrix[1][4] = 1;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
    matrix[2][3] = 1;
    matrix[2][4] = 1;

    matrix[3][0] = 0;
    matrix[3][1] = 1;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
    matrix[3][4] = 1;

    matrix[4][0] = 0;
    matrix[4][1] = 1;
    matrix[4][2] = 1;
    matrix[4][3] = 1;
    matrix[4][4] = 0;

    return matrix;
}

int main() {
    /*
    Para definir a matriz a ser testada, usar o método getMatrixA() ou getMatrixB()
    o tamanho é definido pelas constantes globais A_SIZE e B_SIZE
    */
    int** matrix = getMatrixTeste();
    int size = TESTE_SIZE;

    MyMatrix myM = MyMatrix(matrix, size, size);
    MyMatrix ot = MyMatrix(myM);

    MyMatrix* toSum = new MyMatrix[size - 1];
    MyMatrix sum = MyMatrix(size, size);

    toSum[0] = MyMatrix(myM);
    std::cout << "M^1" << std::endl;
    printMatrix(toSum[0]);
    
    for (int i = 1; i < (size - 1); i++) {
        toSum[i] = myMultiplyMatrices(myM, toSum[i - 1]);
        std::cout << "M^" << i + 1 << std::endl;
        printMatrix(toSum[i]);
    }

    for (int i = 0; i < (size - 1); i++) {
        sum = mySumMatrices(sum, toSum[i]);
    }
    
    std::cout << "Soma final:" << std::endl;
    printMatrix(sum);

    bool isConnected = true;

    for (int i = 0; i < sum.lines; i++) {
        for (int j = 0; j < sum.columns; j++) {
            if (i == j) {
                continue;
            }
            if (sum.matrix[i][j] == 0) {
                isConnected = false;
                break;
            }
        }
    }

    if (isConnected == true) {
        std::cout << "O grafo eh conexo!" << std::endl;
    } else {
        std::cout << "O grafo não eh conexo!" << std::endl;
    }

    return 0;
}
