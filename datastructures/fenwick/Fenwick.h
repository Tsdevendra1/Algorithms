//
// Created by Tharuka Devendra on 01/06/2020.
//

#ifndef ALGORITHMS_FENWICK_H
#define ALGORITHMS_FENWICK_H

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


class Fenwick {
    vector<int> tree;

public:
    void construct(vector<int> initialArray) {
        tree.resize(initialArray.size()+1);
        for (int i = 0; i < initialArray.size(); ++i) {
            int treeIndex = i + 1;
            tree[treeIndex] = initialArray[i];
        }

        for (int i = 0; i < initialArray.size(); ++i) {
            int treeIndex = i + 1;
            int parentIndex = treeIndex + (treeIndex & -treeIndex);
            tree[parentIndex] += tree[treeIndex];
        }
    }

    int prefixSum(int index) {
        int current = index + 1;
        int sum = 0;
        while (current > 0) {
            sum += tree[current];
            current -= (current & -current);
        }
        return sum;
    }

    void add(int index, int value) {
        int current = index + 1;
        while (current < tree.size()) {
            tree[current] += value;
            current += (current & -current);
        }
    }

};

void testFenwick();

#endif //ALGORITHMS_FENWICK_H
