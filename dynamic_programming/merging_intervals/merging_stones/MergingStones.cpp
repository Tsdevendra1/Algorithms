//
// Created by Tharuka Devendra on 20/09/2020.
//

#include "MergingStones.h"
#include "vector"
#include "iostream"
#include "../../../arrays/range_query/RangeQuery.h"

using namespace std;

bool canMergeArray(int arraySize, int mergeSize) {
    int numberRemovedAfterEachMerge = mergeSize - 1;
    int remainingAfterMerge = (arraySize) % numberRemovedAfterEachMerge;
    return remainingAfterMerge == 1 || mergeSize == 2;
}


int getMaxScoreForMergingStonesBottomUp(vector<int> &stones, int mergeSize) {
    int n = stones.size();
    if (!canMergeArray(n, mergeSize)) {
        return -1;
    }
    auto rangeQuery = make_unique<RangeQuery>(stones);
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int subArraySize = mergeSize; subArraySize <= n; ++subArraySize) {
        for (int subArrayStart = 0; subArrayStart <= n - subArraySize; ++subArrayStart) {
            int subArrayEnd = (subArrayStart + subArraySize) - 1;
            dp[subArrayStart][subArrayEnd] = INT_MAX;
            for (int firstPileEnd = subArrayStart; firstPileEnd < subArrayEnd; firstPileEnd += (mergeSize - 1)) {
                int current = dp[subArrayStart][subArrayEnd];
                int splittingLeft = dp[subArrayStart][firstPileEnd];
                int splittingRight = dp[firstPileEnd + 1][subArrayEnd];
                int potentialNew = splittingLeft + splittingRight;
                if (canMergeArray(subArraySize, mergeSize)) {
                    int mergeCost = rangeQuery->getRangeQuery(subArrayStart, subArrayEnd);
                    potentialNew += mergeCost;
                }
                dp[subArrayStart][subArrayEnd] = min(current, potentialNew);
            }
        }
    }
    return dp[0].back();
}

void testMergingStones() {
    vector<int> stones = {3, 2, 4, 1};
    int mergeSize = 2;
    assert(getMaxScoreForMergingStonesBottomUp(stones, mergeSize) == 20);
}
