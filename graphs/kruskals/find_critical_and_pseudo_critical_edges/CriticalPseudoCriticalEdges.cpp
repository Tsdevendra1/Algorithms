//
// Created by Tharuka Devendra on 03/08/2020.
//

#include "CriticalPseudoCriticalEdges.h"
#include "iostream"
#include "vector"
#include "unordered_set"

using namespace std;

class UnionFindCopy {
    vector<int> groupSize;
    vector<int> parents;

public:
    int numberOfGroups;

    explicit UnionFindCopy(int numNodes) {
        numberOfGroups = numNodes;
        groupSize.resize(numNodes);
        parents.resize(numNodes);
        for (int i = 0; i < numNodes; ++i) {
            groupSize[i] = 1;
            parents[i] = i;
        }
    }

    int findParent(int node) {
        int parent = node;
        while (parents[parent] != parent) {
            parent = parents[parent];
        }

        int currentNode = node;
        while (currentNode != parent) {
            int next = parents[currentNode];
            parents[currentNode] = parent;
            currentNode = next;
        }

        return parent;
    }

    void unifyGroups(int node1, int node2) {
        if (areConnected(node1, node2)) {
            return;
        }

        int parentOfNode1 = findParent(node1);
        int parentOfNode2 = findParent(node2);

        if (groupSize[parentOfNode1] > groupSize[parentOfNode2]) {
            groupSize[parentOfNode1] += groupSize[parentOfNode2];
            parents[parentOfNode2] = parentOfNode1;
        } else {
            groupSize[parentOfNode2] += groupSize[parentOfNode1];
            parents[parentOfNode1] = parentOfNode2;
        }

        --numberOfGroups;
    }

    bool areConnected(int node1, int node2) {
        return findParent(node1) == findParent(node2);
    }
};

class KruskalsCriticalPseudoCritical {
    vector<vector<int>> edges;
    int numNodes;

    static bool compareFunc(vector<int> &edge1, vector<int> &edge2) {
        return edge1[2] < edge2[2];
    }

    int kruskals(int ignoreEdge, int forceAddEdge) {
        sort(edges.begin(), edges.end(), compareFunc);
        auto unionFind = new UnionFindCopy(numNodes);
        int cost = 0;
        vector<vector<int>> minSpanEdges;
        if (forceAddEdge != -1) {
            auto edge = edges[forceAddEdge];
            unionFind->unifyGroups(edge[0], edge[1]);
            cost += edge[2];
        }
        for (int i = 0; i < edges.size(); ++i) {
            if (i == ignoreEdge) {
                continue;
            }
            auto edge = edges[i];
            if (!unionFind->areConnected(edge[0], edge[1])) {
                unionFind->unifyGroups(edge[0], edge[1]);
                cost += edge[2];
                minSpanEdges.push_back(edge);
            }
        }
        return unionFind->numberOfGroups == 1 ? cost : INT_MAX;
    }


public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edgesCopy) {
        edges = edgesCopy;
        int counter = 0;
        for (auto &edge: edges) {
            edge.push_back(counter);
            ++counter;
        }
        vector<vector<int>> answer = {{},
                                      {}};
        numNodes = n;
        int originalMinSpanTreeCost = kruskals(-1, -1);
        for (int i = 0; i < edges.size(); ++i) {
            int costWithBlocked = kruskals(i, -1);
            int costWithForceIncluded = kruskals(-1, i);
            if (costWithBlocked > originalMinSpanTreeCost) {
                answer[0].push_back(edges[i][3]);
            } else if (costWithForceIncluded == originalMinSpanTreeCost) {
                answer[1].push_back(edges[i][3]);
            }

        }
        return answer;
    }
};

void testCriticalPseudoCriticalEdges() {
    int numNodes = 6;
    vector<vector<int>> edges = {{0, 1, 1},
                                 {1, 2, 1},
                                 {0, 2, 1},
                                 {2, 3, 4},
                                 {3, 4, 2},
                                 {3, 5, 2},
                                 {4, 5, 2}};
    auto solution = make_unique<KruskalsCriticalPseudoCritical>();
    vector<vector<int>> answer = {{3},
                                  {0, 1, 2, 4, 5, 6}};
    auto foundAnswer = solution->findCriticalAndPseudoCriticalEdges(numNodes, edges);
    assert(foundAnswer[0] == answer[0]);
    assert(foundAnswer[1].size() == answer[1].size());
}
