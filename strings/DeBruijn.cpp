//
// Created by Tharuka Devendra on 30/05/2020.
//

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
#include <numeric>
#include <sstream>
using namespace std;

#include "DeBruijn.h"

unordered_set<string> seen;
vector<int> edges;

void dfs(string node, int &k, string &A) {

    for (int i = 0; i < k; ++i) {
        string str = node + A[i];
        if (seen.find(str) == seen.end()) {
            seen.insert(str);
            // remove back add a new to the front
            dfs(str.substr(1), k, A);
            edges.push_back(i);
        }
    }

}

string deBruijn(int n, int k, string A) {

    // Clearing global variables
    seen.clear();
    edges.clear();

    string startingNode = string(n - 1, A[0]);
    dfs(startingNode, k, A);

    string S;

    // Number of edges
    int l = pow(k, n);

    for (int i = 0; i < l; ++i)
        S += A[edges[i]];
    S += startingNode;

    return S;
}

void testDeBruijn(){
    int n = 2, k = 2;
    string A = "01";
    cout << deBruijn(n, k, A);
}
