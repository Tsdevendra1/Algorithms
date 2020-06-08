//
// Created by Tharuka Devendra on 08/06/2020.
//

#include "Prims.h"
class Compare {
public:
    bool operator () (Edge one, Edge two){
        return one.cost > two.cost;
    }
};
vector<Edge> prims(Graph &graph) {
    vector<Edge> minSpanTree;
    int numNodes = graph.numberOfNodes();
    int numEdges = 0;
    vector<bool> seenNodes(numNodes, false);
    priority_queue<Edge, vector<Edge>, Compare> pq;

    // setup for starting node
    seenNodes[2] = true;
    for (auto &[neighbour, cost]: graph.neighboursForVertex(2)){
        if (!seenNodes[neighbour]) {
            pq.push(Edge{2, neighbour, cost});
        }
    }

    while (!pq.empty() && numEdges < numNodes -1) {
        Edge currentEdge = pq.top();
        int to = currentEdge.to;
        pq.pop();

        if (seenNodes[to]){
            continue;
        }

        seenNodes[to] = true;
        for (auto &[neighbour, cost]: graph.neighboursForVertex(to)){
            if (!seenNodes[neighbour]) {
                pq.push(Edge{to, neighbour, cost});
            }
        }
        minSpanTree.push_back(currentEdge);
        ++numEdges;
    }

    if(numEdges != numNodes - 1) {
        return {};
    }

    return minSpanTree;
}
void testPrims(){
    auto graph = make_unique<Graph>(true);
    graph->addEdge(2,0, 0);
    graph->addEdge(2,5, 6);
    graph->addEdge(0,5, 7);
    graph->addEdge(0,3, 5);
    graph->addEdge(0,1, 9);
    graph->addEdge(5,3, 2);
    graph->addEdge(5,6, 1);
    graph->addEdge(3,6, 3);
    graph->addEdge(3,1, -2);
    graph->addEdge(1,6, 4);
    graph->addEdge(1,4, 3);
    graph->addEdge(6,4, 6);
    vector<Edge> minSpanTree = prims(*graph);
    int spanCost = 0;
    for (auto edge : minSpanTree) {
        spanCost+= edge.cost;
    }
    assert (spanCost == 9);
    cout << endl;


}