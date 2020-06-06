//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "KruskalsAlgorithm.h"
#include "../GraphClass/Graph.h"
#include "../../datastructures/union_find/UnionFind.h"

using namespace std;

struct Edge {
    int to;
    int from;
    int cost;
};

void kruskalsAlgorithm(Graph *graph) {
    vector<Edge> edges;
    for (const auto &[edge, neighbours]: graph->edges) {
        for (const auto &[neighbour, cost]: neighbours) {
            Edge newEdge = Edge{edge, neighbour, cost};
            edges.push_back(newEdge);
        }
    }

    auto compareFunction = [](Edge first, Edge second) {
        return first.cost < second.cost;
    };

    sort(edges.begin(), edges.end(), compareFunction);
    auto unionFind = make_unique<UnionFind>(edges.size());
    vector<Edge> minSpanEdges;

    for (auto edge: edges) {
        if (!unionFind->areConnected(edge.to, edge.from)) {
            unionFind->unify(edge.to, edge.from);
            minSpanEdges.push_back(edge);
        }
    }

    for (auto edge: minSpanEdges){
        cout << edge.to << "->" << edge.from << endl;
    }

}

void testKruskalsAlgorithm() {
    auto graph = new Graph();
    graph->setupSimpleDag();
    kruskalsAlgorithm(graph);
}