//
// Created by Tharuka Devendra on 19/08/2020.
//

#include "IterativeDFSPaths.h"
#include "vector"
#include "unordered_set"
#include "stack"
#include "iostream"

using namespace std;

vector<vector<int>> allPathsSourceTargetMemoryEfficient(vector<vector<int>> &graph) {
    //let use convert the recursive method to iterative way
    vector<vector<int>> allpath;
    if (graph.empty()) return allpath;
    vector<int> path;

    stack<int> nodeStack;
    vector<stack<int>> nodeParents(graph.size());
    vector<int> numberOfChildren(graph.size(), 0);
    nodeStack.push(0);
    int endNode = (int) graph.size() - 1;
    while (!nodeStack.empty()) {
        int currentNode = nodeStack.top();
        nodeStack.pop();
        path.push_back(currentNode);
        if (currentNode == endNode) {
            allpath.push_back(path);
        } else {
            numberOfChildren[currentNode] = graph[currentNode].size();
            for (int neighbour : graph[currentNode]) {
                nodeParents[neighbour].push(currentNode);
                nodeStack.push(neighbour);
            }
        }

        while (numberOfChildren[currentNode] == 0 && currentNode != 0) {
            //update its parents numberOfChildren number
            int currParent = nodeParents[currentNode].top();
            nodeParents[currentNode].pop();
            if (currParent >= 0 && currParent < graph.size())
                numberOfChildren[currParent]--;

            path.pop_back();
            currentNode = path.back();
        }
    }
    return allpath;
}


vector<vector<int>> allPathsSourceTargetMemoryEfficient2(vector<vector<int>> &graph, int endNode){
    vector<vector<int>> answer;

    stack<int> stk;
    vector<int> path = {};

    stk.push(0);
    while (!stk.empty()) {
        int current = stk.top();
        if (path.size() >= 1 && current == path.back()) {
            stk.pop();
            path.pop_back();
            continue;
        }
        path.push_back(current);
        if (current == endNode) {
            answer.push_back(path);
            path.pop_back();
            stk.pop();
            continue;
        }
        for (int neighbor : graph[current]) {
            stk.push(neighbor);
        }
    }
    return answer;
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph, int endNode) {
    vector<vector<int>> answer;
    stack<pair<int, vector<int>>> tracker;
    tracker.push({0, {0}});
    while (!tracker.empty()) {
        int currentNode = tracker.top().first;
        auto path = tracker.top().second;
        tracker.pop();
        if (currentNode == endNode) {
            answer.push_back(path);
        }
        for (auto neighbour: graph[currentNode]) {
            path.push_back(neighbour);
            tracker.push({neighbour, path});
            path.pop_back();
        }
    }
    return answer;
}


void testIterativeDFSPaths() {
    vector<vector<int>> grid = {{1, 2},
                                {3},
                                {3},
                                {}};
//    auto paths = getAllPaths(grid);
    auto paths = allPathsSourceTargetMemoryEfficient(grid);
    auto paths2 = allPathsSourceTargetMemoryEfficient2(grid, 3);
    auto paths3 = allPathsSourceTarget(grid, 3);
    assert(paths.size() == 2);
    assert(paths2.size() == 2);
}
