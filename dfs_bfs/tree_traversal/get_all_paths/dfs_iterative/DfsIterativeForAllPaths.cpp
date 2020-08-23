//
// Created by Tharuka Devendra on 23/08/2020.
//

#include "DfsIterativeForAllPaths.h"
#include "vector"
#include "stack"
#include "unordered_map"
#include "iostream"
#include "../../../../Utils.h"

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

vector<vector<int>> dfsIterativeForAllPathsMemoryEfficient(vector<vector<int>> &graph, int targetNode) {
    stack<int> nodeTracker;
    nodeTracker.push(0);
    vector<int> currentPath = {};
    vector<vector<int>> answer;
    unordered_map<int, int> childrenVisitedTracker;

    for (int node = 0; node < graph.size(); ++node) {
        vector<int> &children = graph[node];
        childrenVisitedTracker[node] = children.size();
    }
    vector<bool> visited(graph.size(), false);
    while (!nodeTracker.empty()) {

        int currentNode = nodeTracker.top();
        nodeTracker.pop();

        currentPath.push_back(currentNode);
        childrenVisitedTracker[currentNode] = graph[currentNode].size();

        if (currentNode == targetNode) {
            answer.push_back(currentPath);
        } else {
            for (auto it = graph[currentNode].rbegin(); it != graph[currentNode].rend(); ++it) {
                int neighbour = *it;
                nodeTracker.push(neighbour);
            }
        }


        // currentNode 0 (start node) si the only node without parents so just continue
        if (currentNode == 0) {
            continue;
        }
        int previousParent = currentPath[currentPath.size() - 2];
        --childrenVisitedTracker[previousParent];
        while (childrenVisitedTracker[currentNode] == 0 && currentNode != 0) {
            currentPath.pop_back();
            currentNode = currentPath.back();
        }

    }

    return answer;
}

vector<vector<int>> dfsIterativeForAllPathsMemoryEfficient2(vector<vector<int>> &graph) {
    //let use convert the recursive method to iterative way
    vector<vector<int>> answer;
    if (graph.size() == 0) return answer;
    vector<int> currentPath;

    stack<int> nodesTracker;
    vector<stack<int>> parentsTracker(graph.size());
    vector<int> childrenVisitedTracker(graph.size(), 0);
    nodesTracker.push(0);

    while (!nodesTracker.empty()) {
        int currentNode = nodesTracker.top();
        nodesTracker.pop();
        currentPath.push_back(currentNode);

        if (currentNode == graph.size() - 1) {
            answer.push_back(currentPath);
        } else {
            childrenVisitedTracker[currentNode] = graph[currentNode].size();
            for (int neighbour : graph[currentNode]) {
                parentsTracker[neighbour].push(currentNode);
                nodesTracker.push(neighbour);
            }
        }

        while (childrenVisitedTracker[currentNode] == 0 && currentNode != 0) {
            int currentParent = parentsTracker[currentNode].top();
            parentsTracker[currentNode].pop();
            childrenVisitedTracker[currentParent]--;
            currentPath.pop_back();
            currentNode = currentPath.back();
        }
    }
    return answer;
}

void testDfsIterativeForAllPaths() {
    vector<vector<int>> adjacencyList = {{1, 2, 3},
                                         {2},
                                         {3},
                                         {}};
    auto allPaths = dfsIterativeForAllPaths(adjacencyList, 3);
    auto allPaths2 = dfsIterativeForAllPathsMemoryEfficient(adjacencyList, 3);
    auto allPaths3 = dfsIterativeForAllPathsMemoryEfficient2(adjacencyList);
    assert(Utils::compareVectors(allPaths, allPaths2));
    assert(Utils::compareVectors(allPaths3, allPaths2));
    assert(allPaths.size() == 3);
    assert(allPaths2.size() == 3);
}

