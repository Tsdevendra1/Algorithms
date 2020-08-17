//
// Created by Tharuka Devendra on 17/08/2020.
//

#include "RangeSumQuery2D.h"
#include "vector"

using namespace std;

class RangeSumQuery2d {

public:
    vector<vector<int>> sumTracker;

    explicit RangeSumQuery2d(vector<vector<int>> &grid) {
        sumTracker.resize(grid.size() + 1, vector<int>(grid[0].size() + 1, 0));
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                sumTracker[row + 1][col + 1] = grid[row][col] + sumTracker[row][col + 1] + sumTracker[row + 1][col] -
                                               sumTracker[row][col];
            }
        }
    }

    int rangeSum2d(pair<int, int> coords1, pair<int, int> coords2) {
        int row1 = coords1.first;
        int col1 = coords1.second;

        int row2 = coords2.first;
        int col2 = coords2.second;
        return sumTracker[row2+1][col2+1] - sumTracker[row1][col2+1] - sumTracker[row2+1][col1] +
               sumTracker[row1][col1];
    }
};

void testRangeSumQuery2D() {
    vector<vector<int>> grid = {{0, 1, 0},
                                {1, 0, 0},
                                {0, 0, 1}};
    auto query = make_unique<RangeSumQuery2d>(grid);
    int answer = query->rangeSum2d({0, 0}, {2, 2});
    assert(answer == 3);
    assert(query->rangeSum2d({0,0}, {0,0}) == 0);
    assert(query->rangeSum2d({0,0}, {0,2}) == 1);
    assert(query->rangeSum2d({0,1}, {0,1}) == 1);
    assert(query->rangeSum2d({0,1}, {2,2}) == 2);
};
