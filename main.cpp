
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
                if (sum < D.matrix[i][j] && (i != j)) {
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

    matrix[0][0] = 0;
    matrix[0][1] = 0;
    matrix[0][2] = 0;
    matrix[0][3] = 1;
    matrix[0][4] = 0;

    matrix[1][0] = 1;
    matrix[1][1] = 0;
    matrix[1][2] = 1;
    matrix[1][3] = 0;
    matrix[1][4] = 1;

    matrix[2][0] = 1;
    matrix[2][1] = 0;
    matrix[2][2] = 0;
    matrix[2][3] = 0;
    matrix[2][4] = 1;

    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 0;
    matrix[3][4] = 1;

    matrix[4][0] = 0;
    matrix[4][1] = 0;
    matrix[4][2] = 0;
    matrix[4][3] = 0;
    matrix[4][4] = 0;

    return matrix;
}

int** getWeightMatrix() {
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 10;
    matrix[0][1] = 10;
    matrix[0][2] = 10;
    matrix[0][3] = 3;
    matrix[0][4] = 10;

    matrix[1][0] = 3;
    matrix[1][1] = 10;
    matrix[1][2] = 1;
    matrix[1][3] = 10;
    matrix[1][4] = 3;

    matrix[2][0] = 1;
    matrix[2][1] = 10;
    matrix[2][2] = 10;
    matrix[2][3] = 10;
    matrix[2][4] = 1;

    matrix[3][0] = 10;
    matrix[3][1] = 10;
    matrix[3][2] = 10;
    matrix[3][3] = 10;
    matrix[3][4] = 3;

    matrix[4][0] = 10;
    matrix[4][1] = 10;
    matrix[4][2] = 10;
    matrix[4][3] = 10;
    matrix[4][4] = 10;

    return matrix;
}

int** getExercicioMediana() {
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 99;
    matrix[0][1] = 3;
    matrix[0][2] = 99;
    matrix[0][3] = 9;
    matrix[0][4] = 6;

    matrix[1][0] = 3;
    matrix[1][1] = 99;
    matrix[1][2] = 2;
    matrix[1][3] = 5;
    matrix[1][4] = 8;

    matrix[2][0] = 99;
    matrix[2][1] = 2;
    matrix[2][2] = 99;
    matrix[2][3] = 1;
    matrix[2][4] = 99;

    matrix[3][0] = 9;
    matrix[3][1] = 5;
    matrix[3][2] = 1;
    matrix[3][3] = 99;
    matrix[3][4] = 5;

    matrix[4][0] = 6;
    matrix[4][1] = 8;
    matrix[4][2] = 99; 
    matrix[4][3] = 5; 
    matrix[4][4] = 99;
    return matrix;
}

int main() {

    // MyMatrix A = MyMatrix(getAdjacencyMatrix(), MATRIX_SIZE, MATRIX_SIZE);
    // std::cout << "Matriz de Adjacencia:\n";
    // A.print();
    
    // MyMatrix R = warshall(A);
    // std::cout << "Matriz de Alcanssabilidade:\n";
    // R.print();

    // MyMatrix B = MyMatrix(getWeightMatrix(), MATRIX_SIZE, MATRIX_SIZE);
    // std::cout << "Matriz de Pesos:\n";
    // B.print();

    // MyMatrix D = floyd_warshall(B);
    // D.print("Matriz com as Menores Distancias:");

    MyMatrix exeMediana = MyMatrix(getExercicioMediana(), MATRIX_SIZE, MATRIX_SIZE);
    MyMatrix minDistance = floyd_warshall(exeMediana);
    exeMediana.print("Matriz de pesos das arestas entre p_i e p_j");
    minDistance.print("Matriz com menores distancias entre p_i e p_j");
    int *wieners = minDistance.getWienerIndexes();
    std::cout << "Indice de Wiener para cada vértice:" << std::endl;
    int minWiener = 99;
    int *minWienerIndex = new int[MATRIX_SIZE];
    int lastIndex = 0;
    for (int i = 0; i < minDistance.lines; ++i) {
        if (wieners[i] < minWiener) {
            minWiener = wieners[i];
            minWienerIndex[i] = i;
            lastIndex++;
        }
        std::cout << "p" << i + 1 << " -> " << wieners[i] << std::endl;
    }

    std::cout << "Conjunto de vértices mediana: {";
    for (int i = 0; i < lastIndex; ++i) {
        if (wieners[minWienerIndex[i]] != minWiener) {
            continue;
        }
        std::cout << "p" << minWienerIndex[i] + 1 << ": " << wieners[minWienerIndex[i]];
        if (i < lastIndex - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    return 0;
}
