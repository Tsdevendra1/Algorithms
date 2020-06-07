//
// Created by Tharuka Devendra on 07/06/2020.
//

#include "BellmanFord.h"
#include "../GraphClass/Graph.h"


vector<int> bellmanFord(Graph &graph, int startNode) {
    int numberOfNodes = graph.numberOfNodes();
    vector<Edge> edges = graph.getEdgesForGraph();
    vector<int> distance(numberOfNodes, INT_MAX);
    distance[startNode] = 0;

    for (int i = 0; i < numberOfNodes - 1; ++i) {
        for (auto edge: edges) {
            if (distance[edge.from] != INT_MAX){
                int travelDistance = distance[edge.from] + edge.cost;
                if (travelDistance < distance[edge.to])
                    distance[edge.to] = travelDistance;
            }
        }
    }

    for (int i = 0; i < numberOfNodes - 1; ++i) {
        for (auto edge: edges) {
            if (distance[edge.from] != INT_MAX) {
                int travelDistance = distance[edge.from] + edge.cost;
                if (travelDistance < distance[edge.to])
                    distance[edge.to] = INT_MIN;
            }
        }
    }
    return distance;
}

void testBellmanFord() {
    auto graph = make_unique<Graph>();
    graph->addEdge(0, 1, 4);
    graph->addEdge(0, 2, 1);
    graph->addEdge(1, 3, 1);
    graph->addEdge(2, 1, 2);
    graph->addEdge(2, 3, 5);
    graph->addEdge(3, 4, 3);
    vector<int> distances = bellmanFord(*graph, 0);
    for (int i = 0; i < (int) distances.size(); ++i) {
        cout << i << " " << distances[i] << endl;
    }

    auto otherGraph = make_unique<Graph>();
    otherGraph->addEdge(0,1,5);
    otherGraph->addEdge(1, 2, 20);
    otherGraph->addEdge(2, 3, 10);
    otherGraph->addEdge(3, 2, -15);
    otherGraph->addEdge(2,4,75);
    otherGraph->addEdge(1,5,60);
    vector<int> distances2 = bellmanFord(*otherGraph, 0);
    for (int i = 0; i < (int) distances2.size(); ++i) {
        cout << i << " " << distances2[i] << endl;
    }
}
