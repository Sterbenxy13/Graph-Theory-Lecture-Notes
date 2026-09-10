
#include <iostream>

#include "common.h"

void steppingStone() {

}

int duality(AllInOneBox matrix, int supplyCount, int demandCount) {

    int counter = 0;

    while (true) {
        // custoOpor = ui + vj - cij
        
        // sistema linear para toda var básica (xij > 0): cij = ui + vj
        // descobre todos os ui e vj
        
        int* supplyCoefs = new int[supplyCount];
        for (int i = 0; i < supplyCount; i++) {
            supplyCoefs[i] = -1000;
        }
        int* demandCoefs = new int[demandCount];
        for (int i = 0; i < demandCount; i++) {
            demandCoefs[i] = -1000;
        }

        
        int basicsCount = supplyCount + demandCount - 1;
        Tuple* backup = new Tuple[basicsCount];
        int lastBackup = 0;
        supplyCoefs[0] = 0;
        for (int i = 0; i < (matrix.memory.size); i++) {    // Define os coeficientes e reserva os que não são determináveis.
            int sI = matrix.memory.memory[i].sIndex;
            int dI = matrix.memory.memory[i].dIndex;
            if (supplyCoefs[sI] < -999 & demandCoefs[dI] < -999) {
                backup[lastBackup] = Tuple();
                backup[lastBackup].sIndex = sI;
                backup[lastBackup].dIndex = dI;
                lastBackup++;
                continue;
            }
            
            if (supplyCoefs[sI] < -999) {
                supplyCoefs[sI] = matrix.matrix[sI][dI].cost - demandCoefs[dI];
            }
            else if (demandCoefs[dI] < -999) {
                demandCoefs[dI] = matrix.matrix[sI][dI].cost - supplyCoefs[sI];
            }
        }

        for (int i = 0; i < lastBackup; i++) { // Define os coeficientes dos restantes.
            int sI = backup[i].sIndex;
            int dI = backup[i].dIndex;

            if (supplyCoefs[sI] < 0) {
                supplyCoefs[sI] = matrix.matrix[sI][dI].cost - demandCoefs[dI];
            }
            if (demandCoefs[dI] < 0) {
                demandCoefs[dI] = matrix.matrix[sI][dI].cost - supplyCoefs[sI];
            }
        }

        // Calcula os /cij para os restantes (xij == 0)
        // o max disso será a nova base
        Tuple max = Tuple();
        max.sIndex = -1;
        max.dIndex = -1;
        int maxOportunityCost = -99;
        int oportunityCost = -1;
        for (int i = 0; i < supplyCount; i++) {
            for (int j = 0; j < demandCount; j++) {
                if (matrix.matrix[i][j].value > 0) {
                    continue;
                }
                oportunityCost = supplyCoefs[i] + demandCoefs[j] - matrix.matrix[i][j].cost;
                if (oportunityCost > maxOportunityCost) {
                    maxOportunityCost = oportunityCost;
                    max.sIndex = i;
                    max.dIndex = j;
                }
            }
        }

        std::cout << max.sIndex << " , " << max.dIndex << ": " << maxOportunityCost << std::endl;

        if (maxOportunityCost <= 0) {
            return counter;
        }
        counter++;

        // construir ciclo fechado a partir dessa nova base, com:
            // Inicia e termina na mesma não básica
            // Formado por horizontal e vertical (i e j)
            // Cada esquina deve ter (x > 0)

        Tuple item = Tuple();
        for (int i = 0; i < matrix.memory.size; i++) { // Busca por vendas que envolvam fornecedor e consumir diferentes.
            item.sIndex = matrix.memory.memory[i].sIndex;
            item.dIndex = matrix.memory.memory[i].dIndex;
            if (item.sIndex == max.sIndex | item.dIndex == max.dIndex) {
                continue;
            }

            if (matrix.matrix[max.sIndex][item.dIndex].value > 0
                and matrix.matrix[item.sIndex][max.dIndex].value > 0
            ) {
                matrix.memory.append(max.sIndex, max.dIndex);
                break;
            }
        }    

        // transfere o menor xij para a nova base e redistribui o ciclo
        int val = 0;
        if (matrix.matrix[max.sIndex][item.dIndex].value
            < matrix.matrix[item.sIndex][max.dIndex].value
        ) {
            matrix.memory.remove(max.sIndex, item.dIndex);
            val = matrix.matrix[max.sIndex][item.dIndex].value;
            matrix.matrix[max.sIndex][max.dIndex].value   = val;
            matrix.matrix[max.sIndex][item.dIndex].value  = 0;
            matrix.matrix[item.sIndex][max.dIndex].value  = matrix.matrix[item.sIndex][max.dIndex].value - val;
            matrix.matrix[item.sIndex][item.dIndex].value = matrix.matrix[item.sIndex][item.dIndex].value + val;
        } else {
            matrix.memory.remove(item.sIndex, max.dIndex);
            val = matrix.matrix[item.sIndex][max.dIndex].value;
            matrix.matrix[max.sIndex][max.dIndex].value   = val;
            matrix.matrix[item.sIndex][max.dIndex].value  = 0;
            matrix.matrix[max.sIndex][item.dIndex].value  = matrix.matrix[item.sIndex][max.dIndex].value - val;
            matrix.matrix[item.sIndex][item.dIndex].value = matrix.matrix[item.sIndex][item.dIndex].value + val;
        }
    }

}

