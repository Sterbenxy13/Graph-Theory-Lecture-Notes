#include <queue>

#include "common.h"

bool createsLoop(const AllInOneBox& problem, int supplyCount, int demandCount, int supplyIndex, int demandIndex) {
    int nodeCount = supplyCount + demandCount;
    int start = supplyIndex;
    int target = supplyCount + demandIndex;
    bool* visited = new bool[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        visited[i] = false;
    }

    std::queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (current == target) {
            delete[] visited;
            return true;
        }

        for (int i = 0; i < problem.memory.size; i++) {
            int rowNode = problem.memory.memory[i].sIndex;
            int columnNode = supplyCount + problem.memory.memory[i].dIndex;
            if (current == rowNode && !visited[columnNode]) {
                visited[columnNode] = true;
                q.push(columnNode);
            }
            if (current == columnNode && !visited[rowNode]) {
                visited[rowNode] = true;
                q.push(rowNode);
            }
        }
    }

    delete[] visited;
    return false;
}

void handleDegeneracy(AllInOneBox& problem, int supplyCount, int demandCount) {
    int requiredBasicVariables = supplyCount + demandCount - 1;

    while (problem.memory.size < requiredBasicVariables) {
        bool allocationAdded = false;

        for (int i = 0; i < supplyCount && !allocationAdded; i++) {
            for (int j = 0; j < demandCount && !allocationAdded; j++) {
                if (problem.memory.contains(i, j)) {
                    continue;
                }

                if (createsLoop(problem, supplyCount, demandCount, i, j)) {
                    continue;
                }

                problem.memory.append(i, j, true);
                problem.matrix[i][j].value = 0;
                problem.matrix[i][j].artificial = true;
                allocationAdded = true;
            }
        }

        if (!allocationAdded) {
            break;
        }
    }
}

AllInOneBox duality(AllInOneBox problem, int supplyCount, int demandCount) {
    handleDegeneracy(problem, supplyCount, demandCount);
    return problem;
}
