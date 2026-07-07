
#include<iostream>

#include "common.h"

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

Memory countingSort(Memory vetor, Node** matrix, int n, int d) {
    Memory result = vetor;

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

Memory radixSort(Memory A, Node** matrix, int supplyCount, int demandCount, int d) {
    Memory result = A;
    for (int i = 1; i <= d; i++) {
        result = countingSort(result, matrix, supplyCount, demandCount, i);
    }

    return result;
}
