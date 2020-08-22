//
// Created by Tharuka Devendra on 22/08/2020.
//

#include "DfsRecursive.h"
#include "vector"
#include "iostream"

using namespace std;

void dfs(int currentNode, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &answer) {
    vector<int> &neighbours = graph[currentNode];
    visited[currentNode] = true;
    answer.push_back(currentNode);

    for (auto neighbour: neighbours) {
        if (!visited[neighbour]) {
            dfs(neighbour, graph, visited, answer);
        }
    }


}

vector<int> dfsRecursive(vector<vector<int>> &graph, int startNode) {
    vector<int> answer;
    vector<bool> visited(graph.size());
    dfs(startNode, graph, visited, answer);
    return answer;
}

void testDfsRecursive() {
    vector<vector<int>> adjacencyList = {{1, 2},
                                         {2},
                                         {0, 3},
                                         {3}};
    auto preorderList = dfsRecursive(adjacencyList, 2);
    vector<int> expected = {2, 0, 1, 3};
    assert(expected == preorderList);
}
