
#pragma once

class MyMatrix {
    public:
        int** matrix;
        int lines;
        int columns;
        
        MyMatrix();
        MyMatrix(int new_lines, int new_columns);
        MyMatrix(int** new_matrix, int new_lines, int new_column);
        MyMatrix(const MyMatrix &other);
        virtual ~MyMatrix();

        int *getWienerIndexes();

        void print();
        void print(std::string title);
};