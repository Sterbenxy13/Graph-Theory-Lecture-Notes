
#include<iostream>

using namespace std;

// 
int* countingSort(int* A, int* B, int n, int k) {
    int* C = new int[k];
    for (int i = 0; i < k; i++) {
        C[i] = 0;
    }

    for (int j = 0; j < n; j++) {
        C[A[j]] = C[A[j]] + 1;
    }

    for (int i = 1; i < k; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j]; // B[C[3] - 1]
        C[A[j]] = C[A[j]] - 1;
    }

    return B;
}

int main() {
    int* A = new int[7];
    int* B = new int[7];

    A[0] = 4;
    A[1] = 3;
    A[2] = 4;
    A[3] = 3;
    A[4] = 1;
    A[5] = 0;
    A[6] = 3;

    for (int i = 0; i < 7; i ++) {
        B[i] = 0;
    }

    int* ordenado = countingSort(A, B, 7, 9);

    for (int i = 0; i<  7; i ++) {
        cout << ordenado[i] << endl;
    }

    return 0;

}

