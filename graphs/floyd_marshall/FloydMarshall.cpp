//
// Created by Tharuka Devendra on 07/06/2020.
//

#include "FloydMarshall.h"
#include "../GraphClass/Graph.h"
#include "../../Utils.h"

pair<vector<vector<int>>, vector<vector<int>>> floydMarshallAlgorithm(Graph &graph) {
    int numNodes = graph.numberOfNodes();
    vector<vector<int>> shortestPath(numNodes, vector<int>(numNodes, INT_MAX));
    vector<vector<int>> nextNode(numNodes, vector<int>(numNodes, INT_MAX));
    for (auto edge : graph.getEdgesForGraph()) {
        shortestPath[edge.from][edge.to] = edge.cost;
        nextNode[edge.from][edge.to] = edge.to;
    }
    for (int k = 0; k < numNodes; ++k) {
        for (int from = 0; from < numNodes; ++from) {
            for (int to = 0; to < numNodes; ++to) {
                if (shortestPath[from][k] != INT_MAX && shortestPath[k][to] != INT_MAX) {
                    if (shortestPath[from][k] + shortestPath[k][to] < shortestPath[from][to]) {
                        shortestPath[from][to] = shortestPath[from][k] + shortestPath[k][to];
                        nextNode[from][to] = nextNode[from][k];
                    }
                }
            }
        }
    }
    // This is for finding negative cycles
    for (int k = 0; k < numNodes; ++k) {
        for (int from = 0; from < numNodes; ++from) {
            for (int to = 0; to < numNodes; ++to) {
                if (shortestPath[from][k] != INT_MAX && shortestPath[k][to] != INT_MAX) {
                    if (shortestPath[from][k] + shortestPath[k][to] < shortestPath[from][to]) {
                        shortestPath[from][to] = INT_MIN;
                        nextNode[from][to] = -1;
                    }
                }
            }
        }
    }
    return {shortestPath, nextNode};

}

vector<int> getShortestPath(Graph &graph, int from, int to) {
    auto[distances, nextNodes] = floydMarshallAlgorithm(graph);
    vector<int> path;
    if (distances[from][to] == INT_MAX) {
        return {};
    }
    int at = from;
    for (; at != to; at = nextNodes[at][to]) {
        if(at ==-1){
            return {};
        }
        path.push_back(at);
    }
    if (nextNodes[at][to] == -1) {
        return {};
    }
    path.push_back(to);
    return path;
}

void testFloydMarshallAlgorithm() {
    auto graph = make_unique<Graph>();
    graph->addEdge(0, 1, 4);
    graph->addEdge(0, 2, 1);
    graph->addEdge(1, 3, 1);
    graph->addEdge(2, 1, 2);
    graph->addEdge(2, 3, 5);
    graph->addEdge(3, 4, 3);
    auto[distances, _] = floydMarshallAlgorithm(*graph);
    cout << distances[1][4] << endl;
    Utils::printArr(getShortestPath(*graph, 0, 4));

    auto otherGraph = make_unique<Graph>();
    otherGraph->addEdge(0,1,5);
    otherGraph->addEdge(1, 2, 20);
    otherGraph->addEdge(2, 3, 10);
    otherGraph->addEdge(3, 2, -15);
    otherGraph->addEdge(2,4,75);
    otherGraph->addEdge(1,5,60);
    auto[distances2, nexNodes2] = floydMarshallAlgorithm(*otherGraph);
    cout << distances2[0][5] << endl;
    Utils::printArr(getShortestPath(*otherGraph, 0, 5));
    Utils::printArr(getShortestPath(*otherGraph, 0, 4));
}
