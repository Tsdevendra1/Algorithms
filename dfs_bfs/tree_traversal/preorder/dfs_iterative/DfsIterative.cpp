//
// Created by Tharuka Devendra on 22/08/2020.
//

#include "DfsIterative.h"
#include "vector"
#include "stack"

using namespace std;

vector<int> dfsIterative(vector<vector<int>> &graph) {
    stack<int> nodeStack;
    nodeStack.push(0);
    vector<int> answer;
    vector<bool> visited(graph.size(), false);

    while (!nodeStack.empty()) {
        int currentNode = nodeStack.top();
        nodeStack.pop();
        // A node from an earlier node could still be in the stack, so need to make sure it doesn't get processed if already visited
        if (visited[currentNode]) {
            continue;
        }
        visited[currentNode] = true;
        answer.push_back(currentNode);

        // needs to be reversed because the child that goes in last gets see first, so to match dfs recursive need do reversed
        reverse(graph[currentNode].begin(), graph[currentNode].end());
        for (auto neighbour: graph[currentNode]) {
            if (!visited[neighbour]) {
                nodeStack.push(neighbour);
            }
        }
    }

    return answer;
}

void testDfsIterative() {
    vector<vector<int>> adjacencyList = {{1, 2},
                                         {2},
                                         {0, 3},
                                         {3}};
    vector<int> traversal = dfsIterative(adjacencyList);
    vector<int> expected = {0, 1, 2, 3};
    assert(traversal == expected);
}
