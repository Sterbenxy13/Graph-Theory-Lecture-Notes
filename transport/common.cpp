
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
 S ,        , Sao_Paulo , Baixada_Santista , Vale_do_Paraiba
   ,    D   ,    50     ,      120         ,       80
60 , Loja_1 ,     8     ,       12         ,       10
40 , Loja_2 ,     4     ,       10         ,        6
50 , Loja_3 ,     6     ,       15         ,       12
,,,,
*/
Node** loadMatrix(std::string relativePath, int SupplyCount, int DemandCount) {

    
    std::ifstream file {relativePath.c_str()};

    if (!file) {
        std::cerr << "Nao foi possivel abrir o arquivo em " << relativePath << std::endl;
        return 0;
    }

    std::string line{};
    file >> line;       // Carrega o cabecalho.
    int colCounter{-1}; // Para não contabilizar a coluna de fornecedores.
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ',') {
            colCounter++;
        }
    }
    Demand* demands = new Demand[colCounter];

    int rowCounter{0}; // Para ignorar a ultima linha(de Demandas)
    while (file >> line) {
        std::cout << line << std::endl;
    }

    file.close();
    std::cout << "content in file: " << line << std::endl;
}
