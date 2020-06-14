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

vector<int> topologicalSortWithWhile(Graph &graph) {
    unordered_map<int, int> indegree;
    for (int node : graph.uniqueNodes){
        indegree[node];
    }
    for (auto &node:graph.uniqueNodes) {
        for (auto &[neighbour, _]: graph.neighboursForVertex(node)) {
            ++indegree[neighbour];
        }
    }
    queue<int> nodesWithNoIncomingEdges;
    for (auto &[node, degree]:indegree) {
        if (degree == 0)
            nodesWithNoIncomingEdges.push(node);
    }
    vector<int> topsort;
    while (!nodesWithNoIncomingEdges.empty()) {
        int current = nodesWithNoIncomingEdges.front();
        nodesWithNoIncomingEdges.pop();
        topsort.push_back(current);
        for (auto &[node, _]: graph.neighboursForVertex(current)) {
            --indegree[node];
            if (indegree[node] == 0) {
                nodesWithNoIncomingEdges.push(node);
            }
        }
    }
    if (topsort.size() != graph.numberOfNodes())
        throw logic_error("detected cycle");
    return topsort;


}


void testTopologicalSort() {
    auto graph = new Graph();
    graph->setupDAG();

    vector<int> sorted = topologicalSort(*graph);
    vector<int> sorted1 = topologicalSortWithWhile(*graph);
    for (auto node: sorted) {
        string letter;
        letter += node + 'a';
        cout << letter << " ";
    }
    cout << endl;
    for (auto node: sorted1) {
        string letter;
        letter += node + 'a';
        cout << letter << " ";
    }
    cout << endl;
}