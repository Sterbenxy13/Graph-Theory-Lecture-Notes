
#include <iostream>

#include "matrix/MyMatrix.h"

MyMatrix warshall(MyMatrix adjacencyMatrix) {
    // R = Reachability Matrix
    MyMatrix R = MyMatrix(adjacencyMatrix);

    for (int k = 0; k < R.lines; ++k) {
        for (int i = 0; i < R.lines; ++i) {
            for (int j = 0; j < R.lines; ++j) {
                R.matrix[i][j] = R.matrix[i][j] | (R.matrix[i][k] & R.matrix[k][j]);
            }
        }
    }
    return R;
}

MyMatrix floyd_warshall(MyMatrix weightMatrix) {
    // D = Minimum Distance Matrix
    MyMatrix D = MyMatrix(weightMatrix);

    for (int k = 0; k < D.lines; ++k) {
        for (int i = 0; i < D.lines; ++i) {
            for (int j = 0; j < D.lines; ++j) {
                int sum = D.matrix[i][k] + D.matrix[k][j];
                if (sum < D.matrix[i][j]) {
                    D.matrix[i][j] = sum;
                }
            }
        }
    }
    return D;
}

#define MATRIX_SIZE 5
int** getAdjacencyMatrix() {
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 110;
    matrix[0][1] = 110;
    matrix[0][2] = 110;
    matrix[0][3] = 1;
    matrix[0][4] = 110;

    matrix[1][0] = 1;
    matrix[1][1] = 110;
    matrix[1][2] = 1;
    matrix[1][3] = 110;
    matrix[1][4] = 1;

    matrix[2][0] = 1;
    matrix[2][1] = 110;
    matrix[2][2] = 110;
    matrix[2][3] = 110;
    matrix[2][4] = 1;

    matrix[3][0] = 110;
    matrix[3][1] = 110;
    matrix[3][2] = 110;
    matrix[3][3] = 110;
    matrix[3][4] = 1;

    matrix[4][0] = 110;
    matrix[4][1] = 110;
    matrix[4][2] = 110;
    matrix[4][3] = 110;
    matrix[4][4] = 110;

    return matrix;
}

int** getWeightMatrix() {
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 0;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 3;
    matrix[0][4] = 0;

    matrix[1][0] = 3;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[1][3] = 0;
    matrix[1][4] = 3;

    matrix[2][0] = 1;
    matrix[2][1] = 0;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 1;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 0;
    matrix[3][4] = 3;

    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[4][3] = 0;
    matrix[4][4] = 0;

    return matrix;
}


int main() {

    MyMatrix A = MyMatrix(getAdjacencyMatrix(), MATRIX_SIZE, MATRIX_SIZE);
    std::cout << "Matriz de Adjacencia:\n";
    A.print();
    
    MyMatrix R = warshall(A);
    std::cout << "Matriz de Alcanssabilidade:\n";
    R.print();

    MyMatrix B = MyMatrix(getWeightMatrix(), MATRIX_SIZE, MATRIX_SIZE);
    std::cout << "Matriz de Pesos:\n";
    B.print();

    MyMatrix D = floyd_warshall(B);
    std::cout << "Matriz com as Menores Distâncias:\n";
    D.print();

    return 0;
}
