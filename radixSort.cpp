
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
