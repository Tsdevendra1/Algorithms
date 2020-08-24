//
// Created by Tharuka Devendra on 24/08/2020.
//

#include "ClimbingStair2D.h"
#include "vector"

using namespace std;

int getMinCost(vector<vector<int>> &grid) {
    vector<vector<int>> dp(grid.size() + 1, vector<int>(grid[0].size() + 1, 0));
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            int minPreviousMove = (row > 0 || col > 0) ? INT_MAX : 0;
            if (row > 0) {
                int oneAbove = dp[row][col + 1];
                minPreviousMove = min(minPreviousMove, oneAbove);
            }
            if (col > 0) {
                int oneLeft = dp[row + 1][col];
                minPreviousMove = min(minPreviousMove, oneLeft);
            }
            int costForCurrentPosition = grid[row][col];
            dp[row + 1][col + 1] = costForCurrentPosition + minPreviousMove;
        }
    }
    return dp.back().back();
}

void testClimbingStairs2d() {

    vector<vector<int>> grid = {{1, 3, 1},
                                {1, 5, 1},
                                {4, 2, 1}};
    assert(getMinCost(grid) == 7);
}
