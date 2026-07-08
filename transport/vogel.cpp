
#include "common.h"

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

    int maxSupplyWeight;
    int minSupplyValue;
    int secMinSupplyValue;

    int maxDemandWeight;
    int minDemandValue;
    int secMinDemandValue;

    Tuple minPos;
    minPos.sIndex;
    minPos.dIndex;

    std::cout << "vai iniciar o while" << std::endl;
    while (remainingDemand > 0) {
        minSupplyValue = 999;
        secMinSupplyValue = 999;
        minPos.sIndex = 0;
        minPos.dIndex = 0;

        for (int i = 0; i < supplyCount; i++) {
            if (supplies[i].capacity <= 0) {
                continue;
            }
            for (int j = 0; j < demandCount; j++) {
                if (demands[i].demand <= 0) {
                    continue;
                }
                if (problem.matrix[i][j].cost < minSupplyValue) {
                    secMinSupplyValue = minSupplyValue;
                    minSupplyValue = problem.matrix[i][j].cost;
                }
            }
            if ((secMinSupplyValue - minSupplyValue) > maxSupplyWeight) {
                minPos.sIndex = i;
                maxSupplyWeight = secMinSupplyValue - minSupplyValue;
            }
        }

        std::cout << "definiu oferta" << std::endl;

        for (int i = 0; i < demandCount; i++) {
            if (demands[i].demand <= 0) {
                continue;
            }
            for (int j = 0; j < supplyCount; j++) {
                if (supplies[i].capacity <= 0) {
                    continue;
                }
                if (problem.matrix[j][i].cost < minDemandValue) {
                    secMinDemandValue = minDemandValue;
                    minDemandValue = problem.matrix[j][i].cost;
                }
                std::cout << "verificando (d,s): " << i << " , " << j << std::endl;
            }
            if ((secMinDemandValue - minDemandValue) > maxDemandWeight) {
                minPos.dIndex = i;
            }
        }

        std::cout << "definiu demanda" << std::endl;

        currentDemand = &(demands[minPos.dIndex]);
        currentSupply = &(supplies[minPos.sIndex]);

        std::cout << "resolveu enderecos" << std::endl;

        currentCapacity = (*currentSupply).capacity;

        std::cout << "pedou capacidade atual" << std::endl;

        currentDemandValue = (*currentDemand).demand;

        std::cout << "pegou demanda atual" << std::endl;

        std::cout << "endereco da memoria: " << &memory << std::endl;
        std::cout << "tamanho da memoria: " << memory->size << std::endl;
        std::cout << "ultimo da memoria: " << memory->getLast().sIndex << " , " << memory->getLast().dIndex << std::endl;

        (*memory).append(minPos.sIndex, minPos.dIndex);

        std::cout << "appendeu memoria" << std::endl;

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

        std::cout << "resolveu ifs" << std::endl;

        (*currentSupply).capacity = currentCapacity - currentReduction;
        (*currentDemand).demand = currentDemandValue - currentReduction;
        remainingDemand = remainingDemand - currentReduction;
        problem.matrix[minPos.sIndex][minPos.dIndex].value = currentReduction;
    }
    return problem;
}

