//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "UnionFind.h"
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

bool UnionFind::areConnected(int node1, int node2) {
    return this->find(node1) == this->find(node2);
}

void UnionFind::unify(int node1, int node2) {

    if (this->areConnected(node1, node2)) {
        return;
    }

    int root1 = this->find(node1);
    int root2 = this->find(node2);

    if (this->groupSize[root1] < this->groupSize[root2]) {
        groupSize[root2] += groupSize[root1];
        parent[root1] = root2;
    } else {
        groupSize[root1] += groupSize[root2];
        parent[root2] = root1;
    }

    --this->numberOfGroups;

}


int UnionFind::find(int node) {
    int root = node;
    while (this->parent[root] != root) {
        root = parent[root];
    }
    // compression part -> make all nodes part of the group point to the root
    while (node != root) {
        int next = parent[node];
        parent[node] = root;
        node = next;
    }

    return root;
}

void testUnionFind() {
    int size = 5;
    auto unionFind = new UnionFind(size);
}

