
#include "common.h"

Tuple blockLine(AllInOneBox problem, int supplyCount, int demandCount) {
    int maxSupplyWeight {-999};
    int minSupplyCost {999};
    int secMinSupplyCost {999};
    Tuple minPos = Tuple();
    for (int s = 0; s < supplyCount; s++) {
        if (problem.supplies[s].capacity <= 0) {
            continue;
        }
        for (int d = 0; d < demandCount; d++) {
            if (problem.demands[d].demand <= 0 | problem.matrix[s][d].value < 0) {
                continue;
            }
            if (problem.matrix[s][d].cost < minSupplyCost) {
                secMinSupplyCost = minSupplyCost;
                minSupplyCost = problem.matrix[s][d].cost;
                minPos.dIndex = d;
            }
            if (problem.matrix[s][d].cost < secMinSupplyCost && problem.matrix[s][d].cost > minSupplyCost) {
                secMinSupplyCost = problem.matrix[s][d].cost;
            }
        }
        if ((secMinSupplyCost - minSupplyCost) > maxSupplyWeight) {
            minPos.sIndex = s;
            maxSupplyWeight = secMinSupplyCost - minSupplyCost;
        }
    }
    minSupplyCost = 999;
    for (int d = 0; d < demandCount; d++) {
        if (problem.demands[d].demand <= 0 | problem.matrix[minPos.sIndex][d].value < 0) {
            continue;
        }
        if (problem.matrix[minPos.sIndex][d].cost < minSupplyCost) {
            minSupplyCost = problem.matrix[minPos.sIndex][d].cost;
            minPos.dIndex = d;
        }
    }
    return minPos;
}

Tuple blockColumn(AllInOneBox problem, int supplyCount, int demandCount) {
    int maxDemandWeight {-999};
    int minDemandCost {999};
    int secMinDemandCost {999};
    Tuple minPos = Tuple();
    for (int d = 0; d < demandCount; d++) {
        if (problem.demands[d].demand <= 0) {
            continue;
        }
        for (int s = 0; s < supplyCount; s++) {
            if (problem.supplies[s].capacity <= 0 | problem.matrix[s][d].value < 0) {
                continue;
            }
            if (problem.matrix[s][d].cost < minDemandCost) {
                secMinDemandCost = minDemandCost;
                minDemandCost = problem.matrix[s][d].cost;
                minPos.sIndex = s;
            }
            if (problem.matrix[s][d].cost < secMinDemandCost && problem.matrix[s][d].cost > minDemandCost) {
                secMinDemandCost = problem.matrix[s][d].cost;
            }
        }
        if ((secMinDemandCost - minDemandCost) > maxDemandWeight) {
            minPos.dIndex = d;
            maxDemandWeight = secMinDemandCost - minDemandCost;
        }
    }
    minDemandCost = 999;
    for (int s = 0; s < supplyCount; s++) {
        if (problem.supplies[s].capacity <= 0 | problem.matrix[s][minPos.dIndex].value < 0) {
            continue;
        }
        if (problem.matrix[s][minPos.dIndex].cost < minDemandCost) {
            minDemandCost = problem.matrix[s][minPos.dIndex].cost;
            minPos.sIndex = s;
        }
    }
    return minPos;
}

AllInOneBox vogel(AllInOneBox problem, int supplyCount, int demandCount) {
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

    Tuple minPos;
    minPos.sIndex;
    minPos.dIndex;
    bool linha = true;
    while (remainingDemand > 0) {

        if (linha) {
            minPos = blockLine(problem, supplyCount, demandCount);
        } else {
            minPos = blockColumn(problem, supplyCount, demandCount);
        }
        linha = ! linha;

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

        (*currentSupply).capacity = (*currentSupply).capacity - currentReduction;
        (*currentDemand).demand = (*currentDemand).demand - currentReduction;
        remainingDemand = remainingDemand - currentReduction;
        problem.matrix[minPos.sIndex][minPos.dIndex].value = currentReduction;
    }
    return problem;
}

