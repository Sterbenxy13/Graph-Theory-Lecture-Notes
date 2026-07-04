
#include <iostream>

#include "common.h"




int main() {

    AllInOneBox matrix = loadMatrix("./transport/matriz.csv", 3, 3);

    for (int i = 0; i < 3; i++) {
        std::cout << matrix.demands[i].name << std::endl;
    }

    // int size {2};
    // Supply* sups = getSupplies(size);

    // for (int i = 0; i < size; i++) {
    //     std::cout << sups[i].name << ", " << sups[i].capacity << std::endl;
    // }

    // Demand* dmds = getDemands(size);

    // for (int i = 0; i < size; i++) {
    //     std::cout << dmds[i].name << ", " << dmds[i].demand << std::endl;
    // }

    // Node** matrix = getMatrix(sups, size, dmds, size);

    // for (int i = 0; i < size; i++) {
    //     for (int j = 0; j < size; i++) {
    //         std::cout << matrix[i][j].cost << ", " << matrix[i][j].value << std::endl;
    //     }
    // }

    return 0;
}
