//
// Created by Tharuka Devendra on 08/06/2020.
//

#include <iostream>
#include "AStar.h"
#include "vector"
#include "numeric"
#include "set"

using namespace std;

using coord = pair<int, int>;
struct Node {
    coord position;
    coord parent;
    double f = 0;
    double h = 0;
    double g = 0;
};

struct cmp {
    bool operator()(Node a, Node b) const {
        return a.f < b.f;
    }
};

bool shouldSkipClosed(Node &node, vector<Node> &closedList) {
    for (auto &closedNode: closedList) {
        if (closedNode.position == node.position)
            return true;
    }
    return false;
}

bool shouldSkipOpen(Node &node, set<Node, cmp> &openList) {

    for (auto &openNode: openList) {
        if (openNode.position == node.position && openNode.f < node.f)
            return true;
    }
    return false;
}

double calculateHeuristic(coord currentPosition, coord endPosition) {
    int xDiff = currentPosition.first - endPosition.first;
    int yDiff = currentPosition.second - endPosition.second;
    return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
}

bool isValid(const vector<vector<int>> &maze, int col, int row) {
    return col >= 0 && row >= 0 && row < maze.size() && col < maze[0].size();
}


vector<coord> unwrapPath(Node currentNode, vector<vector<Node>> &cellDetails) {
    vector<coord> path;
    Node current = currentNode;
    while (current.parent.first != current.position.first || current.parent.second != current.position.second){
        path.push_back(current.position);
        current = cellDetails[current.parent.second][current.parent.first];
    }
    path.emplace_back(current.position.first, current.position.second);
    return path;
}

vector<coord> AStar(vector<vector<int>> &maze, coord start, coord end) {
    auto startNode = Node{start, start};

    // need custom compare function here
    set<Node, cmp> openList;
    openList.insert(startNode);
    vector<Node> closedList;
    vector<coord> possibleMoves = {{0,  -1},
                                   {0,  1},
                                   {-1, 0},
                                   {1,  0},
                                   {-1, -1},
                                   {-1, 1},
                                   {1,  -1},
                                   {1,  1}};
    vector<vector<Node>> cellDetails(maze.size(), vector<Node>(maze[0].size()));
    cellDetails[startNode.position.second][startNode.position.first] = startNode;
    while (!openList.empty()) {
        Node currentNode = *openList.begin();
        openList.erase(openList.begin());

        closedList.push_back(currentNode);
        // check end condition
        if (currentNode.position == end) {
            // handle returning the full path
            return unwrapPath(currentNode, cellDetails);
        }

        vector<Node> children;
        for (coord move : possibleMoves) {
            int newX = currentNode.position.first + move.first;
            int newY = currentNode.position.second + move.second;

            if (isValid(maze, newX, newY) && maze[newY][newX] != 1) {
                children.push_back(Node{{newX, newY}, currentNode.position});
            }
        }
        // generate children


        for (Node child: children) {
            if (shouldSkipClosed(child, closedList)) {
                continue;
            }

            child.g = currentNode.g + 1;
            child.h = calculateHeuristic(child.position, end);
            child.f = child.g + child.h;

            if (shouldSkipOpen(child, openList)) {
                continue;
            }

            openList.insert(child);
            cellDetails[child.position.second][child.position.first] = child;
        }
        // look at children
        // check open list for better
        // check closed list for better
    }

    assert(0);

}

void testAStar() {
    vector<vector<int>> maze = {{0, 1, 0},
                                {1, 0, 0}};
    vector<coord> path = AStar(maze, {0, 0}, {2, 1});
    for (coord position: path) {
        cout << position.first << " " << position.second << endl;
    }
}