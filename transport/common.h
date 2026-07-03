
#ifndef COMMON
#define COMMON

#include <iostream>

struct Demand {
    std::string name;
    int demand;
};

struct Node {
    int cost;
    int value;
};

struct Supply {
    std::string name;
    int capacity;
};

int getInt(std::string message);

std::string getString(std::string);

Demand* getDemands(int size);

Node getNode(std::string message);

Supply* getSupplies(int size);

Node** getMatrix(Supply* supplies, int supplyCount, Demand* demands, int demandCount);

Node** loadMatrix(std::string relativePath, int SupplyCount, int DemandCount);

#endif