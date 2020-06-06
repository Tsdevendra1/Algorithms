//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "KruskalsAlgorithm.h"
#include "../GraphClass/Graph.h"

void kruskalsAlgorithm(Graph *graph) {

}

void testKruskalsAlgorithm() {
    auto graph = new Graph();
    graph->setupDAG();
    kruskalsAlgorithm(graph);
}