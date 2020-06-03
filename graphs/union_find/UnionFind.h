//
// Created by Tharuka Devendra on 03/06/2020.
//

#ifndef ALGORITHMS_UNIONFIND_H
#define ALGORITHMS_UNIONFIND_H

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


class UnionFind {
    int size;
    int numberOfGroups;
    vector<int> groupSize;
    vector<int> parent;

public:
    explicit UnionFind(int size) : size(size) {
        groupSize.resize(size);
        parent.resize(size);

        this->size = size;
        this->numberOfGroups = size;

        for (int i = 0; i < size; ++i) {
            // all components at the start
            groupSize[i] = 1;
            // they are their own parent
            parent[i] = i;
        }
    }

    int find(int node);

    bool areConnected(int node1, int node2);

    void unify(int node1, int node2);


};


void testUnionFind();

#endif //ALGORITHMS_UNIONFIND_H
