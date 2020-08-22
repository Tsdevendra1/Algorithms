//
// Created by Tharuka Devendra on 22/08/2020.
//

#include "DfsRecursiveForAllPaths.h"
#include "vector"
#include "iostream"

using namespace std;

void
dfsForAllPaths(int currentNode, vector<int> &currentPath, int targetNode, vector<bool> &visited,
               vector<vector<int>> &graph,
               vector<vector<int>> &answer) {

    currentPath.push_back(currentNode);
    visited[currentNode] = true;

    if (currentNode == targetNode) {
        answer.push_back(currentPath);
    } else {
        for (auto neighbour: graph[currentNode]) {
            if (visited[neighbour]) {
                continue;
            }
            dfsForAllPaths(neighbour, currentPath, targetNode, visited, graph, answer);
        }
    }
    currentPath.pop_back();
    visited[currentNode] = false;

}

vector<vector<int>> dfsRecursiveForAllPaths(vector<vector<int>> &graph, int startNode, int endNode) {
    vector<vector<int>> answer;
    vector<int> currentPath = {};
    vector<bool> visited(graph.size());
    dfsForAllPaths(startNode, currentPath, endNode, visited, graph, answer);
    return answer;
}

void testDfsRecursiveForAllPaths() {
    vector<vector<int>> adjacencyList = {{1, 2},
                                         {3},
                                         {3},
                                         {}};
    auto allPaths = dfsRecursiveForAllPaths(adjacencyList, 0, 3);
    assert(allPaths.size() == 2);
}
