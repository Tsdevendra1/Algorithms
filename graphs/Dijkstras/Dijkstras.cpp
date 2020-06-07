//
// Created by Tharuka Devendra on 07/06/2020.
//

#include "Dijkstras.h"
#include "../GraphClass/Graph.h"
#include "vector"
#include "../../Utils.h"

using namespace std;

pair<vector<int>, vector<int>> dijkstras(Graph &graph) {
    vector<int> distances(graph.numberOfNodes(), INT_MAX);
    vector<int> visited(graph.numberOfNodes(), 0);
    vector<int> parentNodes(graph.numberOfNodes(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto[costToCurrentNode, currentNode] = pq.top();
        cout << currentNode << endl;
        pq.pop();

        visited[currentNode] = 1;

        // removes stale nodes // alternatively you could just check if you had alreday seen this node
        if (costToCurrentNode > distances[currentNode])
            continue;

        for (auto &[neighbour, cost]: graph.neighboursForVertex(currentNode)) {
            if (visited[neighbour] == 1) {
                continue;
            }
            int costToNeighbour = cost + costToCurrentNode;
            if (costToNeighbour < distances[neighbour]) {
                parentNodes[neighbour] = currentNode;
                distances[neighbour] = costToNeighbour;
                pq.push({costToNeighbour, neighbour});
            }
        }

    }
    return {distances, parentNodes};
}

vector<int> getShortestPathToNode(Graph &graph, int node) {
    auto [distances, parentNodes] = dijkstras(graph);
    vector<int> path;
    while(parentNodes[node] != INT_MAX) {
        path.push_back(node);
        node = parentNodes[node];
    }
    path.push_back(0);

    return path;
}


void testDijkstras() {
    auto graph = make_unique<Graph>();
    graph->addEdge(0, 1, 4);
    graph->addEdge(0, 2, 1);
    graph->addEdge(1, 3, 1);
    graph->addEdge(2, 1, 2);
    graph->addEdge(2, 3, 5);
    graph->addEdge(3, 4, 3);
    auto [distances, parentNodes] = dijkstras(*graph);
    for (int i = 0; i < (int) distances.size(); ++i) {
        cout << i << " " << distances[i] << endl;
    }

    auto path = getShortestPathToNode(*graph, 4);
    Utils::printArr(path);
}
