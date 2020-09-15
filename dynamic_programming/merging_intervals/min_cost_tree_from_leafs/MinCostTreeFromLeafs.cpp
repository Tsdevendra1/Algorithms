//
// Created by Tharuka Devendra on 10/09/2020.
//

#include "MinCostTreeFromLeafs.h"
#include "vector"
#include "iostream"

using namespace std;

int getMinCostFromLeafs(vector<int> &leafValues) {
    // inclusive
    vector<vector<int>> maxForIndexRange(leafValues.size(), vector<int>(leafValues.size()));
    vector<vector<int>> dp(leafValues.size(), vector<int>(leafValues.size()));

    int answer = 0;
    for (int subArrayStart = 0; subArrayStart < leafValues.size(); ++subArrayStart) {
        int maxFound = INT_MIN;
        for (int subArrayEnd = subArrayStart; subArrayEnd < leafValues.size(); ++subArrayEnd) {
            int newestValue = leafValues[subArrayEnd];
            maxFound = max(maxFound, newestValue);
            maxForIndexRange[subArrayStart][subArrayEnd] = maxFound;
        }
    }

    for (int subArraySize = 2; subArraySize <= leafValues.size(); ++subArraySize) {
        for (int subArrayStart = 0; subArrayStart <= leafValues.size() - subArraySize; ++subArrayStart) {
            int subArrayEnd = (subArrayStart + subArraySize) - 1;
            dp[subArrayStart][subArrayEnd] = INT_MAX;
            for (int splittingPoint = subArrayStart; splittingPoint < subArrayEnd; ++splittingPoint) {
                int leftSideMax = maxForIndexRange[subArrayStart][splittingPoint];
                int rightSizeMax = maxForIndexRange[splittingPoint + 1][subArrayEnd];
                int product = leftSideMax * rightSizeMax;
                int current = dp[subArrayStart][splittingPoint] + dp[splittingPoint + 1][subArrayEnd] + product;
                int previous = dp[subArrayStart][subArrayEnd];
                dp[subArrayStart][subArrayEnd] = min(current, previous);
            }
        }
    }

    return dp[0].back();
}

void testMinCostTreeFromLeafs() {
    // https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/submissions/
    vector<int> leafValues = {6, 2, 4};
    assert(getMinCostFromLeafs(leafValues) == 32);
};
