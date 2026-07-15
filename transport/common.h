
#ifndef COMMON
#define COMMON

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
    int head = 0;
    int size;

    void init(int supplyCount, int demandCount) {
        for (int i = 0; i < supplyCount; i++) {
            for (int j = 0; j < demandCount; j++) {
                this->append(i, j);
            }
        }
    }

    void append(int supplyIndex, int demandIndex) {
        memory[size] = Tuple();
        memory[size].sIndex = supplyIndex;
        memory[size].dIndex = demandIndex;
        size++;
    }

    Tuple getFirst() {
        return this->memory[head];
    }

    Tuple getLast() {
        return this->memory[this->size - 1];
    }

    bool contains(int supplyIndex, int demandIndex) {
        bool result = false;
        for (int i = 0; i < size; i++) {
            if (this->memory[i].sIndex == supplyIndex & this->memory[i].dIndex == demandIndex) {
                result = true;
            }
        }
        return result;
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