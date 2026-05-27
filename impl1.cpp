
#include <iostream>

using namespace std;

#include "radixSort.cpp"

int* reverseSort(int* arr, int size) {
    int temp = 0;
    int* result = radixSort(arr, size, 1);
    int high = 0;
    for (int low = 0; low < size / 2; low++) {
        high = size - 1 - low;
        cout << "invertendo: " << result[low] << " com " << result[high] << ".\n";
        temp = result[high];
        result[high] = result[low];
        result[low] = temp;
    }
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

    degrees = reverseSort(degrees, numberOfDegrees);

    if (lastIndex == numberOfDegrees) {
        for (int i = numberOfDegrees - 1; i >= 0; --i) {
            if (degrees[i] != 0) {
                lastIndex = i + 1;
            }
        }
    }

    for (
        int i = 1;
        degrees[0] > 0 & i < numberOfDegrees;
        i++
    ) {
        degrees[0]--;
        degrees[i]--;
        if (degrees[i] < 0) {
            return false;
        }
    }
    if (degrees[0] > 0) {
        return false;
    }

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

int* getIntInput(int vertexNumber) {
    int* result = new int[vertexNumber];
    for (int i = 0; i < vertexNumber; i++) {
        cin >> result[i];
    }
    return result;
}

int main() {

    int size = getSize();
    int* intTest = getIntInput(size);

    cout << "{";
    for (int i = 0; i < size; i++) {
	cout << intTest[i] << ", ";
    }
    cout << "}" << endl;
    
    int* possibles = radixSort(intTest, size, 1);
    int lastIndex = size - 1;
    for (int i = size - 1; i >= 0; --i) {
        if (possibles[i] == 0) {
            lastIndex = i;
        } else {
            break;
        }
    }    

    bool temp = verifyIfAnIntegerSequenceCanBeAGraphVertexesDegreeConfiguration(intTest, size, size);
    if (temp == true) {
        cout << "pode!\n";
    } else {
        cout << "nao pode!\n";
    }
    
    return 0;
}
