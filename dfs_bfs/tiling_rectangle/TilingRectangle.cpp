//
// Created by Tharuka Devendra on 05/08/2020.
//

#include "TilingRectangle.h"
#include "iostream"
#include "vector"
#include "iostream"
#include "numeric"
#include "vector"
#include "numeric"
#include "map"
#include "algorithm"
#include "unordered_map"
#include "queue"

using namespace std;

class TileRectangle {
public:
    int rows;
    int cols;
    int currentBest = INT_MAX;
    vector<vector<bool>> grid;

    void coverGrid(int startRow, int startCol, int squareSize) {
        for (int i = startRow; i < startRow + squareSize; ++i) {
            for (int j = startCol; j < startCol + squareSize; ++j) {
                grid[i][j] = true;
            }
        }
    }

    void uncoverGrid(int startRow, int startCol, int squareSize) {
        for (int i = startRow; i < startRow + squareSize; ++i) {
            for (int j = startCol; j < startCol + squareSize; ++j) {
                grid[i][j] = false;
            }
        }
    }

    void dfs(int currentRow, int currentCol, int numBlocksUsed) {

        if (numBlocksUsed >= currentBest) {
            return;
        }

        if (currentCol >= cols) {
            dfs(currentRow + 1, 0, numBlocksUsed);
            return;
        }

        if (currentRow >= rows) {
            currentBest = numBlocksUsed;
            return;
        }

        if (grid[currentRow][currentCol]) {
            dfs(currentRow, currentCol + 1, numBlocksUsed);
            return;
        }

        int maxBlockUsable = min(cols - currentCol, rows - currentRow);
        // start with best possible solution
        for (int blockSize = maxBlockUsable;
             blockSize >= 1; --blockSize) {
            if (isAvailable(currentRow, currentCol, blockSize)) {
                coverGrid(currentRow, currentCol, blockSize);
                dfs(currentRow, currentCol + 1, numBlocksUsed + 1);
                uncoverGrid(currentRow, currentCol, blockSize);
            }
        }

    }

    bool isAvailable(int startRow, int startCol, int squareSize) {
        for (int i = 0; i < squareSize; ++i) {
            for (int j = 0; j < squareSize; ++j) {
                if (grid[startRow + i][startCol + j]) {
                    return false;
                }
            }
        }
        return true;
    }

    int numberOfSquaresToFill(int rowsCopy, int colsCopy) {
        this->rows = rowsCopy;
        this->cols = colsCopy;
        grid.resize(rows, vector<bool>(cols, false));
        dfs(0, 0, 0);
        return currentBest;
    }

};

int numberOfSquaresToFillBFS(int rows, int cols) {

    auto isComplete = [](vector<vector<bool>> &grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                if (!grid[row][col]) {
                    return false;
                }
            }
        }
        return true;
    };

    auto cover = [](vector<vector<bool>> &grid, bool shouldCover, int row, int col, int blockSize) {
        for (int i = 0; i < blockSize; ++i) {
            for (int j = 0; j < blockSize; ++j) {
                grid[row + i][col + j] = shouldCover;
            }
        }
    };

    auto canCover = [](vector<vector<bool>> &grid, int row, int col, int blockSize) {
        for (int i = 0; i < blockSize; ++i) {
            for (int j = 0; j < blockSize; ++j) {
                if (grid[row + i][col + j]) {
                    return false;
                }
            }
        }
        return true;
    };

    vector<vector<bool>> startGrid(rows, vector<bool>(cols, false));
    queue<tuple<int, vector<vector<bool>>, vector<int>>> tracker;
    int answer = INT_MAX;
    tracker.push({0, startGrid, {}});

    while (!tracker.empty()) {
        auto currentTop = tracker.front();
        int numberOfSquaresUsed = get<0>(currentTop);
        auto grid = get<1>(currentTop);
        auto history = get<2>(currentTop);
        tracker.pop();

        if (isComplete(grid)) {
            return numberOfSquaresUsed;
        }

        int unfilledCol;
        int unfilledRow;
        bool foundUnfilled = false;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (!grid[row][col]) {
                    unfilledRow = row;
                    unfilledCol = col;
                    foundUnfilled = true;
                    break;
                }
            }
            if (foundUnfilled)
                break;
        }

        int maxBlockSize = min(rows - unfilledRow, cols - unfilledCol);

        for (int blockSize = maxBlockSize; blockSize >= 1; --blockSize) {

            if (!canCover(grid, unfilledRow, unfilledCol, blockSize)) {
                continue;
            }

            cover(grid, true, unfilledRow, unfilledCol, blockSize);
            history.push_back(blockSize);

            tracker.push({numberOfSquaresUsed + 1, grid, history});

            cover(grid, false, unfilledRow, unfilledCol, blockSize);
            history.pop_back();
        }
    }
    return answer;
}

void testTilingRectangle() {
    int rows = 5;
    int cols = 8;
    auto solution = new TileRectangle();
    assert(solution->numberOfSquaresToFill(rows, cols) == 5);
    assert(solution->numberOfSquaresToFill(2, 3) == 3);
    assert(numberOfSquaresToFillBFS(11, 13) == 6);
    assert(numberOfSquaresToFillBFS(5, 8) == 5);
    assert(numberOfSquaresToFillBFS(2, 3) == 3);
}
