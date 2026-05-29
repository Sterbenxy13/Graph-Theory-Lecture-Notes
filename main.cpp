
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

#define MATRIX_SIZE 9
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

int** getExercicioMediana1() {

    /*
        a = 0 = p1
        b = 1 = p2
        c = 2 = p3
        d = 3 = p4
        e = 4 = p5
    */
    
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

int** getExercicioMediana2() {

    /*
        a = 0 = p1
        b = 1 = p2
        c = 2 = p3
        d = 3 = p4
        e = 4 = p5
    */
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 99;
    matrix[0][1] = 4;
    matrix[0][2] = 6;
    matrix[0][3] = 99;
    matrix[0][4] = 99;

    matrix[1][0] = 4;
    matrix[1][1] = 99;
    matrix[1][2] = 2;
    matrix[1][3] = 99;
    matrix[1][4] = 99;

    matrix[2][0] = 6;
    matrix[2][1] = 2;
    matrix[2][2] = 99;
    matrix[2][3] = 1;
    matrix[2][4] = 5;

    matrix[3][0] = 99;
    matrix[3][1] = 99;
    matrix[3][2] = 1;
    matrix[3][3] = 99;
    matrix[3][4] = 3;

    matrix[4][0] = 99;
    matrix[4][1] = 99;
    matrix[4][2] = 5; 
    matrix[4][3] = 3; 
    matrix[4][4] = 99;
    return matrix;
}

int** getExercicioMediana3() {

    /*
        a = 0 = p1
        b = 1 = p2
        c = 2 = p3
        d = 3 = p4
        e = 4 = p5
    */
    
    int** matrix = new int*[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        matrix[i] = new int[MATRIX_SIZE];
    }

    matrix[0][0] = 99;
    matrix[0][1] = 12;
    matrix[0][2] = 22;
    matrix[0][3] = 15;
    matrix[0][4] = 99;
    matrix[0][5] = 99;
    matrix[0][6] = 25;
    matrix[0][7] = 99;
    matrix[0][8] = 99;

    matrix[1][0] = 12;
    matrix[1][1] = 99;
    matrix[1][2] = 8;
    matrix[1][3] = 99;
    matrix[1][4] = 16;
    matrix[1][5] = 99;
    matrix[1][6] = 99;
    matrix[1][7] = 99;
    matrix[1][8] = 99;

    matrix[2][0] = 22;
    matrix[2][1] = 8;
    matrix[2][2] = 99;
    matrix[2][3] = 99;
    matrix[2][4] = 99;
    matrix[2][5] = 17;
    matrix[2][6] = 99;
    matrix[2][7] = 99;
    matrix[2][8] = 40;

    matrix[3][0] = 15;
    matrix[3][1] = 99;
    matrix[3][2] = 99;
    matrix[3][3] = 99;
    matrix[3][4] = 15;
    matrix[3][5] = 99;
    matrix[3][6] = 14;
    matrix[3][7] = 99;
    matrix[3][8] = 99;

    matrix[4][0] = 99;
    matrix[4][1] = 16;
    matrix[4][2] = 99; 
    matrix[4][3] = 15; 
    matrix[4][4] = 99;
    matrix[4][5] = 10;
    matrix[4][6] = 99;
    matrix[4][7] = 16;
    matrix[4][8] = 99;

    matrix[5][0] = 99;
    matrix[5][1] = 99;
    matrix[5][2] = 17; 
    matrix[5][3] = 99; 
    matrix[5][4] = 10;
    matrix[5][5] = 99;
    matrix[5][6] = 99;
    matrix[5][7] = 99;
    matrix[5][8] = 18;

    matrix[6][0] = 25;
    matrix[6][1] = 99;
    matrix[6][2] = 99; 
    matrix[6][3] = 14; 
    matrix[6][4] = 99;
    matrix[6][5] = 99;
    matrix[6][6] = 99;
    matrix[6][7] = 13;
    matrix[6][8] = 21;

    matrix[7][0] = 99;
    matrix[7][1] = 99;
    matrix[7][2] = 99; 
    matrix[7][3] = 99; 
    matrix[7][4] = 16;
    matrix[7][5] = 99;
    matrix[7][6] = 13;
    matrix[7][7] = 99;
    matrix[7][8] = 11;

    matrix[8][0] = 99;
    matrix[8][1] = 99;
    matrix[8][2] = 40; 
    matrix[8][3] = 99; 
    matrix[8][4] = 99;
    matrix[8][5] = 18;
    matrix[8][6] = 21;
    matrix[8][7] = 11;
    matrix[8][8] = 99;
    return matrix;
}

int main() {

    // Exercício 01

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

    // MyMatrix exeMediana = MyMatrix(getExercicioMediana1(), MATRIX_SIZE, MATRIX_SIZE);
    // MyMatrix minDistance = floyd_warshall(exeMediana);
    // exeMediana.print("Matriz de pesos das arestas entre p_i e p_j");
    // minDistance.print("Matriz com menores distancias entre p_i e p_j");
    // int *wieners = minDistance.getWienerIndexes();
    // std::cout << "Indice de Wiener para cada vértice:" << std::endl;
    // int minWiener = 99;
    // int *minWienerIndex = new int[MATRIX_SIZE];
    // int lastIndex = 0;
    // for (int i = 0; i < minDistance.lines; ++i) {
    //     if (wieners[i] < minWiener) {
    //         minWiener = wieners[i];
    //         minWienerIndex[i] = i;
    //         lastIndex++;
    //     }
    //     std::cout << "p" << i + 1 << " -> " << wieners[i] << std::endl;
    // }

    // std::cout << "Conjunto de vértices mediana: {";
    // for (int i = 0; i < lastIndex; ++i) {
    //     if (wieners[minWienerIndex[i]] != minWiener) {
    //         continue;
    //     }
    //     std::cout << "p" << minWienerIndex[i] + 1 << ": " << wieners[minWienerIndex[i]];
    //     if (i < lastIndex - 1) {
    //         std::cout << ", ";
    //     }
    // }
    // std::cout << "}" << std::endl;

    // Exercício 02

    // MyMatrix exeMediana = MyMatrix(getExercicioMediana2(), MATRIX_SIZE, MATRIX_SIZE);
    // int* pesosVertices = new int[MATRIX_SIZE];
    // pesosVertices[0] = 3;
    // pesosVertices[1] = 1;
    // pesosVertices[2] = 2;
    // pesosVertices[3] = 1;
    // pesosVertices[4] = 4;
    // MyMatrix minDistance = floyd_warshall(exeMediana);
    // MyMatrix minWeightedDistance = MyMatrix(minDistance);
    // for (int j = 0; j < minWeightedDistance.columns; ++j) {
    //     for (int i = 0; i < minWeightedDistance.lines; ++i) {
    //         if (i == j) {
    //             continue;
    //         }
    //         minWeightedDistance.matrix[i][j] = minWeightedDistance.matrix[i][j] * pesosVertices[j];
    //     }
    // }
    // exeMediana.print("Matriz de pesos das arestas entre p_i e p_j");
    // minDistance.print("Matriz com menores distancias entre p_i e p_j");
    // minWeightedDistance.print("Matriz com as menores distancias ajustadas por peso do vértice destino");

    // int *wieners = minDistance.getWienerIndexes();
    // std::cout << "Indice de Wiener para cada vertice:" << std::endl;
    // int minWiener = 99;
    // int *minWienerIndex = new int[MATRIX_SIZE];
    // int lastIndex = 0;
    // for (int i = 0; i < minDistance.lines; ++i) {
    //     if (wieners[i] < minWiener) {
    //         minWiener = wieners[i];
    //         minWienerIndex[i] = i;
    //         lastIndex++;
    //     }
    //     std::cout << "p" << i + 1 << " -> " << wieners[i] << std::endl;
    // }

    // std::cout << "Conjunto de vertices mediana: {";
    // for (int i = 0; i < lastIndex; ++i) {
    //     if (wieners[minWienerIndex[i]] != minWiener) {
    //         continue;
    //     }
    //     std::cout << "p" << minWienerIndex[i] + 1 << ": " << wieners[minWienerIndex[i]];
    //     if (i < lastIndex - 1) {
    //         std::cout << ", ";
    //     }
    // }
    // std::cout << "}" << std::endl;

    // wieners = minWeightedDistance.getWienerIndexes();
    // std::cout << "Indice de Wiener ajustado para cada vertice:" << std::endl;
    // minWiener = 99;
    // minWienerIndex = new int[MATRIX_SIZE];
    // lastIndex = 0;
    // for (int i = 0; i < minWeightedDistance.lines; ++i) {
    //     if (wieners[i] < minWiener) {
    //         minWiener = wieners[i];
    //         minWienerIndex[i] = i;
    //         lastIndex++;
    //     }
    //     std::cout << "p" << i + 1 << " -> " << wieners[i] << std::endl;
    // }

    // std::cout << "Conjunto de vertices mediana com peso ajustado: {";
    // for (int i = 0; i < lastIndex; ++i) {
    //     if (wieners[minWienerIndex[i]] != minWiener) {
    //         continue;
    //     }
    //     std::cout << "p" << minWienerIndex[i] + 1 << ": " << wieners[minWienerIndex[i]];
    //     if (i < lastIndex - 1) {
    //         std::cout << ", ";
    //     }
    // }
    // std::cout << "}" << std::endl;

    // Exercício 03

    MyMatrix exeMediana = MyMatrix(getExercicioMediana3(), MATRIX_SIZE, MATRIX_SIZE);
    MyMatrix minDistance = floyd_warshall(exeMediana);
    exeMediana.print("Matriz de pesos das arestas entre p_i e p_j");
    minDistance.print("Matriz com menores distancias entre p_i e p_j");

    int *wieners = minDistance.getWienerIndexes();
    std::cout << "Indice de Wiener para cada vertice:" << std::endl;
    int minWiener = 300;
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

    std::cout << "Conjunto de vertices mediana: {";
    for (int i = 0; i < lastIndex; ++i) {
        if (wieners[minWienerIndex[i]] > minWiener) {
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
