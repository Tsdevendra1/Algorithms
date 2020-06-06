//
// Created by Tharuka Devendra on 06/06/2020.
//

#include "LongShortDagPath.h"
#include "../GraphClass/Graph.h"
#include "../../Utils.h"

using namespace std;

int
topologicalSortDfs(int index, int currentNode, Graph &graph, vector<int> &seen, vector<int> &topologicalSort) {
    seen[currentNode] = 1;
    const unordered_map<int, int> &neighbours = graph.neighboursForVertex(currentNode);
    for (auto &[neighbour, _]: neighbours) {
        if (seen[neighbour] == 0) {
            index = topologicalSortDfs(index, neighbour, graph, seen, topologicalSort);
        }
    }
    topologicalSort[index] = currentNode;
    return index - 1;
}

vector<int> _topologicalSort(Graph &graph) {
    vector<int> topologicalSort(graph.numberOfNodes());
    vector<int> seen(graph.numberOfNodes());
    int index = graph.numberOfNodes() - 1;
    for (auto &node:graph.uniqueNodes) {

        if (seen[node] == 0) {
            index = topologicalSortDfs(index, node, graph, seen, topologicalSort);
        }
    }
    return topologicalSort;
}

unordered_map<char, int> shortestPathDag(Graph &graph) {
    vector<int> topological = _topologicalSort(graph);
    Utils::printArr(topological);
    unordered_map<char, int> shortestPath;
    for (int node: topological) {
        const unordered_map<int, int> &neighbours = graph.neighboursForVertex(node);
        int costForCurrent = shortestPath[node];
        for (auto &[neighbour, travelCost]: neighbours) {
            int costForNeighbour = costForCurrent + travelCost;
            if (shortestPath.find(neighbour) == shortestPath.end() || costForNeighbour < shortestPath[neighbour]) {
                shortestPath[neighbour] = costForNeighbour;
            }
        }
    }

    return shortestPath;
}

unordered_map<char, int> longestPathDag(Graph graph) {
    // main difference here is we multiply all edge weights by minus one
    vector<int> topological = _topologicalSort(graph);
    Utils::printArr(topological);
    unordered_map<char, int> longestPath;
    for (int node: topological) {
        const unordered_map<int, int> &neighbours = graph.neighboursForVertex(node);
        int costForCurrent = longestPath[node];
        for (auto &[neighbour, travelCost]: neighbours) {
            // make the travel cost negative is the main difference
            int costForNeighbour = costForCurrent + -travelCost;
            if (longestPath.find(neighbour) == longestPath.end() || costForNeighbour < longestPath[neighbour]) {
                longestPath[neighbour] = costForNeighbour;
            }
        }
    }

    return longestPath;
}

void testLongestAndShortedDAG() {
    auto graph = make_unique<Graph>();
    graph->addEdge('a', 'b', 3);
    graph->addEdge('a', 'c', 6);
    graph->addEdge('b', 'e', 11);
    graph->addEdge('b', 'd', 4);
    graph->addEdge('b', 'c', 4);
    graph->addEdge('c', 'd', 8);
    graph->addEdge('c', 'g', 11);
    graph->addEdge('d', 'e', -4);
    graph->addEdge('d', 'f', 5);
    graph->addEdge('d', 'g', 2);
    graph->addEdge('e', 'h', 9);
    graph->addEdge('f', 'h', 1);
    graph->addEdge('g', 'h', 2);

    // See william fitset video to verify this (was correct at the time of commit)
    auto shortestPath = shortestPathDag(*graph);
    for (auto &[node, cost]: shortestPath) {
        string r;
        r += node + 'a';
        cout << r << " " << cost << endl;
    }

    cout << endl;

    auto longestPath = longestPathDag(*graph);
    for (auto &[node, cost]: longestPath) {
        string r;
        r += node + 'a';
        cout << r << " " << cost << endl;
    }
}

