<<<<<<< HEAD

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
    int *wieners = minDistance.getWienerIndex();
    for (int i = 0; i < minDistance.lines; ++i) {
        std::cout << "p" << i + 1 << " -> " << wieners[i] << std::endl;
    }

    return 0;
}
=======

#include <iostream>

using namespace std;

#include "radixSort.cpp"

int* invert(int* arr, int size) {
    int temp = 0;
    int* result = radixSort(arr, size, 1);
    int high = 0;
    for (
        int low = 0; 
        low < size / 2; 
        low++
    ) {
        high = size - 1 - low;
        cout << "invertendo: " << result[low] << " com " << result[high] << ".\n";
        temp = result[high];
        result[high] = result[low];
        result[low] = temp;
    }
    // for (
    //     int low, high = 0; 
    //     low < size / 2; 
    //     low++, high--
    // ) {
    //     high = size - 1 - low;
    //     cout << "invertendo: " << result[low] << " com " << result[high] << ".\n";
    //     temp = result[high];
    //     result[high] = result[low];
    //     result[low] = temp;
    // }
    return result;
}

bool verifyIfAnIntegerSequenceCanBeAGraphVertexesDegreeConfiguration(int* degrees, int numberOfDegrees, int lastIndex) {

    if (lastIndex < 0) {
        for (int i = 0; i < numberOfDegrees; i++) {
            if (degrees[i] != 0) {
                return false;
            }
        }
        return true;
    }

    degrees = invert(degrees, numberOfDegrees);
    cout << "invertido: {";
    for (int i = 0; i < numberOfDegrees; i++) {
        cout << degrees[i] << ', ';
    }
    cout << "}" << endl;

    for (
        int i = 1;
        degrees[0] > 0 & i < numberOfDegrees;
        i++
    ) {
        degrees[0]--;
        degrees[i]--;
        cout << "a";
        if (degrees[i] < 0) {
            return false;
        }
    }
    if (degrees[0] > 0) {
        return false;
    }

    for (int i = 0; i < numberOfDegrees; i++) {
        cout << degrees[i];
    }
    cout <<  endl;

    if (verifyIfAnIntegerSequenceCanBeAGraphVertexesDegreeConfiguration(degrees, numberOfDegrees, lastIndex - 1)) {
        return true;
    } else {
        return false;
    }
}

int getSize() {
    int result = 0;
    cout << "Insira o número de vértices: ";
    cin >> result;
    return result;
}

char* getInput(int vertexNumber) {
    char* result = new char[vertexNumber];
    cout << "Graus dos vértices sem espaços: ";
    cin >> result;
    return result;
}

int* getIntInput(int vertexNumber) {
    int* result = new int[vertexNumber];
    for (int i = 0; i < vertexNumber; i++) {
        cin >> result[i];
    }
    return result;
}


int parseChar(char c) {
    return c - 48;
}

int* parseString(char* s) {
    int size = (sizeof(s) / sizeof(*s));
    int* result = new int[size];
    for (int i = 0; i < size; i++) {
        result[i] = parseChar(s[i]);
    }
    return result;
}

int main() {

//    char* txt = getInput();
    char* txt = new char[2];
    txt[0] = 'a';
    txt[1] = 'b';
    int size = getSize();
    int* intTest = getIntInput(size);

    int* intxt = parseString(txt);
    cout << "{";
    for (int i = 0; i < 2; i++) {
	cout << intxt[i] << ", ";
    }
    cout << "}" << endl;

    cout << "{";
    for (int i = 0; i < size; i++) {
	cout << intTest[i] << ", ";
    }
    cout << "}" << endl;
    
    int* test = new int[5];

    test[0] = 3;
    test[1] = 3;
    test[2] = 3;
    test[3] = 3;
    test[4] = 2;

//    bool temp = verifyIfAnIntegerSequenceCanBeAGraphVertexesDegreeConfiguration(test, 5, 0);
    
    int* possibles = radixSort(intTest, size, 1);
    int lastIndex = size - 1;
    cout << "ordenados: {";
    for (int i = 0; i < size; i++) {
        if (possibles[i] == 0) {
            lastIndex = size - 1 - i;
        }
        cout << possibles[i];
    }
    cout << "}" << endl;

    

    bool temp = verifyIfAnIntegerSequenceCanBeAGraphVertexesDegreeConfiguration(possibles, size, lastIndex);
    if (temp == true) {
        cout << "pode!\n";
    } else {
        cout << "nao pode!\n";
    }
    
    return 0;
}
>>>>>>> ec70df5 (repo init)
