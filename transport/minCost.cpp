
#include "common.h"

AllInOneBox minCost(AllInOneBox problem, int supplyCount, int demandCount) {
    Memory* memory = problem.initMemory(supplyCount, demandCount);

    Demand* demands = problem.demands;
    Supply* supplies = problem.supplies;

    int remainingDemand {0};
    for (int i = 0; i < demandCount; i++) {
        remainingDemand = remainingDemand + demands[i].demand;
    }

    int currentReduction {0};
    int currentCapacity {0};
    int currentDemandValue {0};

    Demand* currentDemand;
    Supply* currentSupply;

    int minValue;
    Tuple minPos;
    minPos.sIndex;
    minPos.dIndex;
    while (remainingDemand > 0) {
        minValue = 999;
        minPos.sIndex = 0;
        minPos.dIndex = 0;
        for (int i = 0; i < supplyCount; i++) {
            for (int j = 0; j < demandCount; j++) {
                if (problem.memory.contains(i, j)) {
                    continue;
                }                
                if (problem.matrix[i][j].value < 0 | problem.matrix[i][j].value > 99) {
                    continue;
                }
                if (problem.matrix[i][j].cost < minValue) {
                    minValue = problem.matrix[i][j].cost;
                    minPos.sIndex = i;
                    minPos.dIndex = j;
                }
            }
        }

        currentDemand = &(demands[minPos.dIndex]);
        currentSupply = &(supplies[minPos.sIndex]);

        currentCapacity = (*currentSupply).capacity;
        currentDemandValue = (*currentDemand).demand;
        (*memory).append(minPos.sIndex, minPos.dIndex);

        if (currentCapacity > currentDemandValue) {
            currentReduction = currentDemandValue;
            for (int i = 0; i < supplyCount; i++) {
                if (problem.memory.contains(i, minPos.dIndex)) {
                    continue;
                }
                problem.matrix[i][minPos.dIndex].value = -1;
            }
        } else if (currentCapacity < currentDemandValue) {
            currentReduction = currentCapacity;
            for (int i = 0; i < demandCount; i++) {
                if (problem.memory.contains(minPos.sIndex, i)) {
                    continue;
                }
                problem.matrix[minPos.sIndex][i].value = -1;
            }
        } else if (currentCapacity == currentDemandValue) {
            currentReduction = currentCapacity;
            for (int i = 0; i < demandCount; i++) {
                if (problem.memory.contains(minPos.sIndex, i)) {
                    continue;
                }
                problem.matrix[minPos.sIndex][i].value = -1;
                problem.matrix[i][minPos.dIndex].value = -1;
            }
        }
        (*currentSupply).capacity = currentCapacity - currentReduction;
        (*currentDemand).demand = currentDemandValue - currentReduction;
        remainingDemand = remainingDemand - currentReduction;
        problem.matrix[minPos.sIndex][minPos.dIndex].value = currentReduction;
    }
    return problem;
}

