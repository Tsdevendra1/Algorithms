//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "TopologicalSort.h"
#include "../GraphClass/Graph.h"
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <stack>
#include <numeric>
#include <sstream>

using namespace std;

int dfs(int currentOrderIndex, int currentNode, Graph graph, vector<int> &ordering, vector<bool> &seen) {
    seen[currentNode] = true;
    unordered_set<int> nodes = graph.neighboursForVertex(currentNode);
    for (auto node: nodes) {
        if (!seen[node]) {
            currentOrderIndex = dfs(currentOrderIndex, node, graph, ordering, seen);
        }
    }
    ordering[currentOrderIndex] = currentNode;
    return currentOrderIndex - 1;

}

vector<int> topologicalSort(const Graph &graph) {
    int numNodes = graph.numberOfNodes();
    vector<bool> seen(numNodes, false);
    vector<int> ordering(numNodes);
    int indexForOrdering = numNodes - 1;

    for (int atNode = 0; atNode < numNodes; ++atNode) {
        if (!seen[atNode]) {
            indexForOrdering = dfs(indexForOrdering, atNode, graph, ordering, seen);
        }
    }
    return ordering;
}


void testTopologicalSort() {
    auto graph = new Graph();
    graph->setupDAG();

    vector<int> sorted = topologicalSort(*graph);
    for (auto node: sorted) {
        string letter;
        letter += node + 'a';
        cout << letter << endl;
    }
}