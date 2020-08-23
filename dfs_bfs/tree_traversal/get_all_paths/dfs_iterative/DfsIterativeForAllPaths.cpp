//
// Created by Tharuka Devendra on 23/08/2020.
//

#include "DfsIterativeForAllPaths.h"
#include "vector"
#include "stack"
#include "iostream"

using namespace std;

vector<vector<int>> dfsIterativeForAllPaths(vector<vector<int>> &graph, int targetNode) {
    stack<pair<int, vector<int>>> nodeTracker;
    nodeTracker.push({0, {0}});
    vector<vector<int>> answer;
    vector<bool> visited(graph.size(), false);
    while (!nodeTracker.empty()) {

        int currentNode = nodeTracker.top().first;
        auto currentPath = nodeTracker.top().second;
        nodeTracker.pop();

        if (currentNode == targetNode) {
            answer.push_back(currentPath);
        } else {
            for (auto it = graph[currentNode].rbegin(); it != graph[currentNode].rend(); ++it) {
                int neighbour = *it;
                currentPath.push_back(neighbour);
                nodeTracker.push({neighbour, currentPath});
                currentPath.pop_back();
            }
        }

    }

    return answer;
}

void testDfsIterativeForAllPaths() {
    vector<vector<int>> adjacencyList = {{1, 2},
                                         {3},
                                         {3},
                                         {}};
    auto allPaths = dfsIterativeForAllPaths(adjacencyList, 3);
    assert(allPaths.size() == 2);
}

