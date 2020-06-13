//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "TopologicalSort.h"
#include "../GraphClass/Graph.h"
#include <vector>
#include <iostream>
#include <unordered_set>
#include <numeric>

using namespace std;
enum Colours {
    white, gray, black
};

int dfs(int currentOrderIndex, int currentNode, Graph &graph, vector<int> &ordering, vector<bool> &seen,
        vector<Colours> &colours, bool &hasCycle) {
    seen[currentNode] = true;
    unordered_map<int, int> nodes = graph.neighboursForVertex(currentNode);
    colours[currentNode] = gray;
    for (auto &[node, cost]: nodes) {
        if (colours[node] == gray) {
            hasCycle = true;
        }
        if (!seen[node]) {
            currentOrderIndex = dfs(currentOrderIndex, node, graph, ordering, seen, colours, hasCycle);
        }
    }
    colours[currentNode] = black;
    ordering[currentOrderIndex] = currentNode;
    return currentOrderIndex - 1;

}

vector<int> topologicalSort(Graph &graph) {
    int numNodes = graph.numberOfNodes();
    vector<bool> seen(numNodes, false);
    vector<int> ordering(numNodes);
    vector<Colours> colours(numNodes, white);
    int indexForOrdering = numNodes - 1;
    bool hasCycle = false;

    for (int atNode = 0; atNode < numNodes; ++atNode) {
        if (!seen[atNode]) {
            indexForOrdering = dfs(indexForOrdering, atNode, graph, ordering, seen, colours, hasCycle);
        }
    }
    if (hasCycle) {
        throw logic_error("Can't topsort - found cycle");
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