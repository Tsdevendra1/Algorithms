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


class Graph {

    unordered_map<int, unordered_set<int>> edges;
    unordered_set<int> uniqueNodes;


public:
    void setupDAG();

    int numberOfNodes() const {
        return (int) uniqueNodes.size();
    };

    void addEdge(int node1, int node2);
    void addEdge(char node1, char node2);
    unordered_set<int> neighboursForVertex(int node) {
        return edges[node];
    };
};


#endif //ALGORITHMS_GRAPH_H
