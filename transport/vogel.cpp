
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
            std::cout << "vendo as linhas, olhei para a pos: " << s << " , " << d << std::endl;
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
            std::cout << "vendo as colunas, olhei para a pos: " << s << " , " << d << std::endl;
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

    std::cout << "vai iniciar o while" << std::endl;

    bool linha = true;

    int nada = 0;
    while (remainingDemand > 0) {
        // minSupplyValue = 999;
        // secMinSupplyValue = 999;
        // minPos.sIndex = 0;
        // minPos.dIndex = 0;

        if (linha) {
            minPos = blockLine(problem, supplyCount, demandCount);
        } else {
            minPos = blockColumn(problem, supplyCount, demandCount);
        }
        linha = ! linha;

        std::cout << "definiu oferta e demanda: " << minPos.sIndex << " , " << minPos.dIndex << std::endl;

        currentDemand = &(demands[minPos.dIndex]);
        currentSupply = &(supplies[minPos.sIndex]);

        std::cout << "resolveu enderecos" << std::endl;

        currentCapacity = (*currentSupply).capacity;

        std::cout << "pegou capacidade atual" << std::endl;

        currentDemandValue = (*currentDemand).demand;

        std::cout << "pegou demanda atual" << std::endl;

        // std::cout << "endereco da memoria: " << &(memory->getLast()) << std::endl;
        // std::cout << "ultimo da memoria: " << memory->getLast().sIndex << " , " << memory->getLast().dIndex << std::endl;
        
        (*memory).append(minPos.sIndex, minPos.dIndex);

        std::cout << "tamanho da memoria: " << memory->size << std::endl;

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

        (*currentSupply).capacity = (*currentSupply).capacity - currentReduction;
        (*currentDemand).demand = (*currentDemand).demand - currentReduction;
        remainingDemand = remainingDemand - currentReduction;
        problem.matrix[minPos.sIndex][minPos.dIndex].value = currentReduction;

        // std::cin >> nada;
    }
    return problem;
}

