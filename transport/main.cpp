
#include <iostream>

#include "common.h"
#include "northWest.cpp"
#include "minCost.cpp"
#include "vogel.cpp"

#include "otimalidade.cpp"

AllInOneBox loadAndPrintData(std::string path, int supplyCount, int demandCount) {
    AllInOneBox matrix = loadMatrix(path, supplyCount, demandCount);

    std::cout << "Consumidores e demandas: " << std::endl;
    for (int i = 0; i < demandCount; i++) {
        std::cout << matrix.demands[i].name << " , " << matrix.demands[i].demand << std::endl;
    }

    std::cout << "Fornecedores e capacidades: " << std::endl;
    for (int i = 0; i < supplyCount; i++) {
        std::cout << matrix.supplies[i].name << " , " << matrix.supplies[i].capacity << std::endl;
    }

    std::cout << "Matriz de custos: " << std::endl;
    for (int i = 0; i < supplyCount; i++) {
        for (int j = 0; j < demandCount; j++) {
            std::cout << matrix.matrix[i][j].cost << ',';
        }
        std::cout << std::endl;
    }

    return matrix;
}

int main() {

    int supplyCount {3};
    int demandCount {3};

    AllInOneBox matrix = loadAndPrintData("./matriz.csv", supplyCount, demandCount);

    std::cout << "Distribuicao:" << std::endl;

    AllInOneBox result = northWestDistribution(matrix, supplyCount, demandCount);
    // AllInOneBox result = minCost(matrix, supplyCount, demandCount);
    // AllInOneBox result = vogel(matrix, supplyCount, demandCount);

    int s {0};
    int d {0};
    int totalCost {0};
    for (int i = 0; i < result.memory.size; i++) {
        s = result.memory.memory[i].sIndex;
        d = result.memory.memory[i].dIndex;
        std::cout << result.supplies[s].name << " entrega " << result.matrix[s][d].value << " para " << result.demands[d].name << " com custo: " << result.matrix[s][d].cost << std::endl;
        totalCost = totalCost + result.matrix[s][d].cost;
    }

    std::cout << "Custo total: " << totalCost << std::endl;
    std::cout << "Z: " << calcZ(result) << std::endl;

    // TESTE DE OTIMALIDADE

    // ITERAÇÃO

    int iterations = duality(result, supplyCount, demandCount);

    totalCost = 0;
    for (int i = 0; i < result.memory.size; i++) {
        s = result.memory.memory[i].sIndex;
        d = result.memory.memory[i].dIndex;
        std::cout << result.supplies[s].name << " entrega " << result.matrix[s][d].value << " para " << result.demands[d].name << " com custo: " << result.matrix[s][d].cost << std::endl;
        totalCost = totalCost + result.matrix[s][d].cost;
    }

    std::cout << "Custo total: " << totalCost << std::endl;
    std::cout << "Z: " << calcZ(result) << std::endl;
    std::cout << "Numero de correcoes: " << iterations << std::endl;

    return 0;
}
