
#include <iostream>

#include "common.h"

AllInOneBox northWestDistribution(AllInOneBox problem, int supplyCount, int demandCount) {
    Memory* memory = problem.initMemory(supplyCount, demandCount);

    Demand* demands = problem.demands;
    Supply* supplies = problem.supplies;

    int demandIndex {0};
    int supplyIndex {0};

    int currentReduction {0};
    int currentCapacity {0};
    int currentDemandValue {0};

    Demand* currentDemand;
    Supply* currentSupply;
    // Node currentNode;
    Tuple currentPosition;
    while (
        (demandIndex < demandCount) 
        & (supplyIndex < supplyCount)
    ) {
        currentDemand = &(demands[demandIndex]);
        currentSupply = &(supplies[supplyIndex]);

        currentCapacity = (*currentSupply).capacity;
        currentDemandValue = (*currentDemand).demand;
        (*memory).append(supplyIndex, demandIndex);
        // currentNode = problem.matrix[supplyIndex][demandIndex];

        if (currentCapacity > currentDemandValue) {
            currentReduction = currentDemandValue;
            demandIndex++;

        } else if (currentCapacity < currentDemandValue) {
            currentReduction = currentCapacity;
            supplyIndex++;

        } else if (currentCapacity == currentDemandValue) {
            currentReduction = currentCapacity;
            demandIndex++;
            supplyIndex++;

        }
        // currentNode.value = currentReduction;
        // (*memory).append(currentNode);

        (*currentSupply).capacity = currentCapacity - currentReduction;
        (*currentDemand).demand = currentDemandValue - currentReduction;
        problem.matrix[memory->getLast().sIndex][memory->getLast().dIndex].value = currentReduction;
    }

    return problem;
}

int main() {

    int supplyCount {3};
    int demandCount {3};

    AllInOneBox matrix = loadMatrix("./transport/matriz.csv", supplyCount, demandCount);

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

    std::cout << "Distribuicao:" << std::endl;

    AllInOneBox path = northWestDistribution(matrix, supplyCount, demandCount);

    int s {0};
    int d {0};
    for (int i = 0; i < path.memory.size; i++) {
        s = path.memory.memory[i].sIndex;
        d = path.memory.memory[i].dIndex;
        std::cout << path.supplies[s].name << " entrega " << path.matrix[s][d].value << " para " << path.demands[d].name << " com custo: " << path.matrix[s][d].cost << std::endl;
    }

    std::cout << "Z: " << calcZ(path) << std::endl;

    return 0;
}
