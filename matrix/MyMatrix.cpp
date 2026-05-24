
#include <iostream>

#include "MyMatrix.h"

MyMatrix::MyMatrix() {
    this->lines = 10;
    this->columns = 10;
    this->matrix = new int*[this->lines];
    for (int i = 0; i < this->lines; i++) {
        this->matrix[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->matrix[i][j] = 0;
        }
    }
}

MyMatrix::MyMatrix(int new_lines, int new_columns) {
    this->lines = new_lines;
    this->columns = new_columns;
    this->matrix = new int*[this->lines];
    for (int i = 0; i < this->lines; i++) {
        this->matrix[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->matrix[i][j] = 0;
        }
    }
}

MyMatrix::MyMatrix(int** new_matrix, int new_lines, int new_columns) {
    this->matrix = new_matrix;
    this->lines = new_lines;
    this->columns = new_columns;
}

MyMatrix::MyMatrix(const MyMatrix &other) {
    this->matrix = other.matrix;
    this->lines = other.lines;
    this->columns = other.columns;
}

MyMatrix::~MyMatrix() {}