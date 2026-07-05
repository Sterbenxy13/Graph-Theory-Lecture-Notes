
#ifndef COMMON
#define COMMON

#include <iostream>

struct Tuple {
    int sIndex;
    int dIndex;
};

struct Node {
    int cost;
    int value;
};

struct Memory {
    Tuple* memory;
    int size;

    void append(int supplyIndex, int demandIndex) {
        memory[size] = Tuple();
        memory[size].sIndex = supplyIndex;
        memory[size].dIndex = demandIndex;
        size++;
    }

    Tuple getLast() {
        return this->memory[this->size - 1];
    }
};

struct Demand {
    int demand;
    std::string name;
};

struct Supply {
    int capacity;
    std::string name;
};

struct AllInOneBox {
    Node**  matrix;
    Demand* demands;
    Supply* supplies;
    Memory memory;

    Memory* initMemory(int supplyCount, int demandCount) {
        int s = supplyCount * demandCount;
        Tuple* list = new Tuple[s];
        this->memory = Memory();
        this->memory.memory = list;
        this->memory.size = 0;
        return &this->memory;    
    }
};


int getInt(std::string message);

std::string getString(std::string);

Demand* getDemands(int size);

Node getNode(std::string message);

Supply* getSupplies(int size);

Node** getMatrix(Supply* supplies, int supplyCount, Demand* demands, int demandCount);

AllInOneBox loadMatrix(std::string relativePath, int SupplyCount, int DemandCount);

Demand* serializeDemandNames(Demand* demands, std::string line);

Demand* serializeDemandValues(Demand* demands, std::string line);

int calcZ(AllInOneBox problem);

#endif