//
// Created by Tharuka Devendra on 07/09/2020.
//

#include "NumberOfPathsForGrid.h"
#include "vector"
#include "iostream"

using namespace std;

int dfs(int currentRow, int currentCol, vector<vector<int>> &dp) {

    if (currentRow == 0 && currentCol == 0) {
        return 1;
    }

    if (currentRow < 0 || currentCol < 0) {
        return 0;
    }

    if (dp[currentRow][currentCol] != 0) {
        return dp[currentRow][currentCol];
    }

    int score = 0;
    score += dfs(currentRow, currentCol - 1, dp);
    score += dfs(currentRow - 1, currentCol, dp);
    dp[currentRow][currentCol] = score;
    return score;

}

int getNumberOfPathsTopDown(int numRows, int numCols) {
    vector<vector<int>> dp(numRows, vector<int>(numCols));
    return dfs(numRows - 1, numCols - 1, dp);
}

int getNumberOfPathsBottomUp(int numRows, int numCols) {
    vector<vector<int>> dp(numRows + 1, vector<int>(numCols + 1));
    for (int col = 0; col < numCols; ++col) {
        dp[1][col + 1] = 1;
    }
    for (int row = 0; row < numRows; ++row) {
        dp[row + 1][1] = 1;
    }
    for (int row = 1; row < numRows; ++row) {
        for (int col = 1; col < numCols; ++col) {
            dp[row + 1][col + 1] = dp[row + 1][col] + dp[row][col + 1];
        }
    }
    return dp.back().back();
}


void testNumberOfPathsForGrid() {

    assert(getNumberOfPathsBottomUp(2, 3) == 3);
    assert(getNumberOfPathsTopDown(2, 3) == 3);
}
