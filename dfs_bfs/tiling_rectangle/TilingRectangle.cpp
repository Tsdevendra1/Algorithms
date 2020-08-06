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
            if (!isAvailable(currentRow, currentCol, blockSize)) {
                break;
            }
            coverGrid(currentRow, currentCol, blockSize);
            dfs(currentRow, currentCol + 1, numBlocksUsed + 1);
            uncoverGrid(currentRow, currentCol, blockSize);
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
        cout << currentBest << endl;
        return currentBest;
    }
};

void testTilingRectangle() {
    int rows = 5;
    int cols = 8;
    auto solution = new TileRectangle();
    assert(solution->numberOfSquaresToFill(rows, cols) == 5);
    assert(solution->numberOfSquaresToFill(2, 3) == 3);
}
