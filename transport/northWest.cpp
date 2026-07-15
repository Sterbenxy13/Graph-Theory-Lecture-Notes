
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

        (*currentSupply).capacity = currentCapacity - currentReduction;
        (*currentDemand).demand = currentDemandValue - currentReduction;
        problem.matrix[memory->getLast().sIndex][memory->getLast().dIndex].value = currentReduction;
    }

    return problem;
}
