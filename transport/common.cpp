
#include <iostream>
#include <fstream>

#include "common.h"

int getInt(std::string message = "Digite um numero: ") {
    int result {0};
    std::cout << message;
    std::cin >> result;
    return result;
}

std::string getString(std::string message = "Digite um texto: ") {
    std::string result {""};
    std::cout << message;
    std::cin >> result;
    return result;
}

Supply getSupply() {
    Supply result {Supply()};
    result.name = getString("Digite o nome do fornecedor: ");
    result.capacity = getInt("Digite a capacidade do fornecedor: ");
    return result;
}

Supply* getSupplies(int size) {
    Supply* result = new Supply[size];
    for (int i = 0; i < size; i++) {
        result[i] = getSupply();
    }
    return result;
}

Demand getDemand() {
    Demand result {Demand()};
    result.name = getString("Digite o nome do consumidor: ");
    result.demand = getInt("Digite a demanda do consumidor: ");
    return result;
}

Demand* getDemands(int size) {
    Demand* result = new Demand[size];
    for (int i = 0; i < size; i++) {
        result[i] = getDemand();
    }
    return result;
}

Node getNode(Supply supply, Demand demand) {
    Node result {Node()};
    result.cost = getInt("Digite o custo de ir de " + supply.name + " para " + demand.name);
    return result;
}

Node** getMatrix(Supply* supplies, int supplyCount, Demand* demands, int demandCount) {
    Node** matrix = new Node*[supplyCount];
    for (int i = 0; i < supplyCount; i++) {
        matrix[i] = new Node[demandCount];
        for (int j = 0; j < demandCount; j++) {
            matrix[i][j] = getNode(supplies[i], demands[j]);
        }
    }
    return matrix;
}

/* Formato:

Ofertas ,          , nomeDmd1 , nomeDmd2
        , Demandas , demanda1 , demanda2
oferta1 , nome_Of1 , custo11  , custo12
oferta1 , nome_Of2 , custo21  , custo22

Exemplo:
       ,  S , Sao_Paulo , Baixada_Santista , Vale_do_Paraiba
   D   ,    ,    50     ,      120         ,       80
Loja_1 , 60 ,     8     ,       12         ,       10
Loja_2 , 40 ,     4     ,       10         ,        6
Loja_3 , 50 ,     6     ,       15         ,       12
,,,,
*/
AllInOneBox loadMatrix(std::string relativePath, int supplyCount, int demandCount) {

    
    std::ifstream file {relativePath.c_str()};

    if (!file) {
        std::cerr << "Nao foi possivel abrir o arquivo em " << relativePath << std::endl;
        return AllInOneBox();
    }
    std::string line{};

    Demand* demands  = new Demand[demandCount];
    for (int i = 0; i < demandCount; ++i) {
        demands[i] = Demand();
    }
    Supply* supplies = new Supply[supplyCount];
    
    // primeira linha: nomes dos consumidores
    file >> line;
    demands = serializeDemandNames(demands, line);

    // segunda linha: demanda dos consumidores
    file >> line;
    demands = serializeDemandValues(demands, line);

    // demais linhas(fornecedores): capacidade, nome, custo... 
    Node** matrix = new Node*[supplyCount];

    std::string supplyName {};
    std::string supplyCapacity {};
    
    int supplyCounter {0};
    int charPos {0};

    std::string cost {};
    int demandCounter {0};
    while (file >> line) {
        std::cout << "linha avaliada: " << line << std::endl;
        matrix[supplyCounter] = new Node[demandCount];
        charPos = 0;

        // primeira coluna: Serializa nome
        supplyName = "";
        while (line[charPos] != ',') {
            supplyName = supplyName + line[charPos];
            ++charPos;
        }
        supplies[supplyCounter].name = supplyName;
        ++charPos;
        
        // segunda coluna: Serializa capacidade
        supplyCapacity = "";
        while (line[charPos] != ',') {
            std::cout << "char avaliado: " << line[charPos] << std::endl;
            supplyCapacity = supplyCapacity + line[charPos];
            charPos++;
        }
        try {
            supplies[supplyCounter].capacity = std::stoi(supplyCapacity);
        } catch (const std::invalid_argument e) {
            std::cerr << "Argumento invalido: " << e.what() << supplyCapacity;
        }
        
        ++charPos;

        // demais colunas: custos do fornecedor para o consumidor
        cost = "";
        demandCounter = 0;
        while (line[charPos] != '\0') {
            if (line[charPos] == ',') {
                matrix[supplyCounter][demandCounter] = Node();
                matrix[supplyCounter][demandCounter].cost = std::stoi(cost);
                cost = "";
                ++demandCounter;
            } else {
                cost = cost + line[charPos];
            }
            ++charPos;
        }
        matrix[supplyCounter][demandCounter] = Node();
        matrix[supplyCounter][demandCounter].cost = std::stoi(cost);

        ++supplyCounter;
    }

    file.close();

    AllInOneBox result = AllInOneBox();
    result.demands = demands;
    result.supplies = supplies;
    result.matrix = matrix;
    return result;
}

Demand* serializeDemandNames(Demand* demands, std::string line) {
    int virgCounter {0};
    int charPos {0};
    while (virgCounter < 2) {
        if (line[charPos] == ',') {
            ++virgCounter;
        }
        ++charPos;
    }
    
    int demandCounter {0};
    std::string demandName {};
    while (line[charPos] != '\0') {
        if (line[charPos] == ',') {
            demands[demandCounter].name = demandName;
            demandName = "";
            ++demandCounter;
        } else {
            demandName = demandName + line[charPos];
        }
        ++charPos;
    }
    demands[demandCounter].name = demandName;
    
    return demands;
}

Demand* serializeDemandValues(Demand* demands, std::string line) {
    int virgCounter {0};
    int charPos {0};
    while (virgCounter < 2) {
        if (line[charPos] == ',') {
            ++virgCounter;
        }
        ++charPos;
    }
    
    int demandCounter {0};
    std::string demandValue {};
    while (line[charPos] != '\0') {
        if (line[charPos] == ',') {
            demands[demandCounter].demand = std::stoi(demandValue);
            demandValue = "";
            ++demandCounter;
        } else {
            demandValue = demandValue + line[charPos];
        }
        ++charPos;
    }
    demands[demandCounter].demand = std::stoi(demandValue);

    return demands;
}
