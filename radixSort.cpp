
#include<iostream>

using namespace std;

int powerTo(int a, int b) {
    if (b == 0) {
        return 1;
    }
    if (b == 1) {
        return a;
    }
    int result = a;
    for (int i = 2; i <= b; i++) {
        result = result * a;
    }
    return result;
}

int* countingSort(int* vetor, int n, int d) {
    int* result = new int[n];

    int* aux = new int[10];
    for (int i = 0; i < 10; i++) {
        aux[i] = 0;
    }

    for (int j = 0; j < n; j++) {
        int naux = (vetor[j] % powerTo(10, d)) / powerTo(10, d - 1);
        aux[naux] = aux[naux] + 1;
    }

    for (int i = 1; i < 10; i++) {
        aux[i] = aux[i] + aux[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        int naux = (vetor[j] % powerTo(10, d)) / powerTo(10, d - 1);
        result[aux[naux] - 1] = vetor[j];
        aux[naux] = aux[naux] - 1;
    }
    return result;
}

int* radixSort(int* A, int n, int d) {
    int* result = A;
    for (int i = 1; i <= d; i++) {
        result = countingSort(result, n, i);
    }

    return result;
}

// int main() {
//     int* A = new int[8];

//     A[0] = 491;
//     A[1] = 348;
//     A[2] = 736;
//     A[3] = 653;
//     A[4] = 231;
//     A[5] = 492;
//     A[6] = 785;
//     A[7] = 111;

//     int* ordenado = radixSort(A, 8, 3);

//     cout << "A:" << endl;
//     for (int i = 0; i <  8; i ++) {
//         cout << A[i] << endl;
//     }

//     cout << "A ordenado:" << endl;
//     for (int i = 0; i <  8; i ++) {
//         cout << ordenado[i] << endl;
//     }

//     return 0;

// }

