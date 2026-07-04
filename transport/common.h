
#ifndef COMMON
#define COMMON

#include <iostream>

struct Demand {
    int demand;
    std::string name;
};

struct Node {
    int cost;
    int value;
};

struct Supply {
    int capacity;
    std::string name;
};

struct AllInOneBox {
    Node**  matrix;
    Demand* demands;
    Supply* supplies;
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

#endif