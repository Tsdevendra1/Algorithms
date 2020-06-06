//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "Graph.h"

void Graph::addEdge(int from, int to, int cost) {
    uniqueNodes.insert(from);
    uniqueNodes.insert(to);
    this->edges[from][to] = cost;
}

void Graph::addEdge(char from, char to, int cost) {
    this->addEdge(from - 'a', to - 'a', cost);
}


void Graph::setupDAG() {
    this->addEdge('c', 'a');
    this->addEdge('c', 'b');

    this->addEdge('e', 'a');
    this->addEdge('e', 'f');
    this->addEdge('e', 'd');


    this->addEdge('f', 'k');
    this->addEdge('f', 'j');

    this->addEdge('j', 'm');
    this->addEdge('j', 'l');

    this->addEdge('d', 'h');
    this->addEdge('d', 'g');

    this->addEdge('h', 'j');
    this->addEdge('h', 'i');

    this->addEdge('a', 'd');
    this->addEdge('b', 'd');
    this->addEdge('k', 'j');
    this->addEdge('i', 'l');
    this->addEdge('g', 'i');

}

void Graph::setupSimpleDag() {
    this->addEdge(0, 1, 10);
    this->addEdge(0, 2, 6);
    this->addEdge(0, 3, 5);
    this->addEdge(1, 3, 15);
    this->addEdge(2, 3, 4);
}
