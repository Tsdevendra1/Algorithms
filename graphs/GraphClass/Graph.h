//
// Created by Tharuka Devendra on 03/06/2020.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

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


struct Edge {
    int from;
    int to;
    int cost;
};

class Graph {

public:
    bool makeUndirected;

    explicit Graph(bool makeUndirected = false) : makeUndirected(makeUndirected) {};
    unordered_set<int> uniqueNodes;

    vector<Edge> getEdgesForGraph() {
        vector<Edge> edgesForGraph;
        for (auto &[node, neighbours]: this->edges) {
            for (auto &[neighbour, cost]: neighbours) {
                edgesForGraph.push_back(Edge{node, neighbour, cost});
            }
        }

        return edgesForGraph;
    }

    void setupDAG();

    unordered_map<int, unordered_map<int, int>> edges;

    void setupSimpleDag();

    int numberOfNodes() const {
        return (int) uniqueNodes.size();
    };

    void addEdge(int node1, int node2, int cost = 0);

    void addEdge(char node1, char node2, int cost = 0);

    unordered_map<int, int> neighboursForVertex(int node) {
        return edges[node];
    };
};


#endif //ALGORITHMS_GRAPH_H
