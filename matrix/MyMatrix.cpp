
#include <iostream>

#include "MyMatrix.h"

MyMatrix::MyMatrix() {
    *this = MyMatrix(10, 10);
}

MyMatrix::MyMatrix(int new_lines, int new_columns) {
    int** matrix = new int*[new_lines];
    for (int i = 0; i < new_lines; i++) {
        matrix[i] = new int[new_columns];
        for (int j = 0; j < new_columns; j++) {
            matrix[i][j] = 0;
        }
    }
    *this = MyMatrix(matrix, new_lines, new_columns);
}

MyMatrix::MyMatrix(int** new_matrix, int new_lines, int new_columns) {
    this->matrix = new_matrix;
    this->lines = new_lines;
    this->columns = new_columns;
}

MyMatrix::MyMatrix(const MyMatrix &other) {
    this->lines = other.lines;
    this->columns = other.columns;
    this->matrix = new int*[other.lines];
    for (int i = 0; i < other.lines; ++i) {
        this->matrix[i] = new int[other.columns];
        for (int j = 0; j < other.columns; ++j) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }

}

MyMatrix::~MyMatrix() {}

int *MyMatrix::getWienerIndex() {
    int *wienerList = new int[this->lines];
    for (int i = 0; i < this->lines; ++i) {
        wienerList[i] = 0;
        for (int j = 0; j < this->columns; ++j) {
            if (i == j) {
                continue;
            }
            wienerList[i] = wienerList[i] + this->matrix[i][j];
        }
    }
    return wienerList;
}

void MyMatrix::print() {
    this->print("");
}

void MyMatrix::print(std::string title) {
    std::cout << title << std::endl;
    
    std::cout << "    | ";
    for (int i = 0; i < this->lines; i++) {
        std::cout << "p" << i + 1 << " | ";
    }
    std::cout << std::endl;
    for (int i = 0; i <= this->columns; i++) {
        std::cout << std::string(4, '-') << '+';
    }
    std::cout << std::endl;

    for (int i = 0; i < this->lines; i++) {
        std::cout << " p" << i + 1 << " | ";
        for (int j = 0; j < this->columns; j++) {
            if (this->matrix[i][j] < 10) {
                std::cout << ' ';
            }
            std::cout << this->matrix[i][j] << " | ";
        }
        std::cout << std::endl;
        for (int i = 0; i <= this->columns; i++) {
            std::cout << std::string(4, '-') << '+';
        }
        std::cout << std::endl;
    }
}