//
// Created by Tharuka Devendra on 21/09/2020.
//

#include "BalloonPopping.h"
#include "vector"
#include "iostream"

using namespace std;

int tempAnswer(vector<int> &nums) {

    int N = nums.size();
    nums.insert(nums.begin(), 1);
    nums.insert(nums.end(), 1);

    // rangeValues[i][j] is the maximum # of coins that can be obtained
    // by popping balloons only in the range [i,j]
    vector<vector<int>> rangeValues(nums.size(), vector<int>(nums.size(), 0));

    // build up from shorter ranges to longer ranges
    for (int len = 1; len <= N; ++len) {
        for (int start = 1; start <= N - len + 1; ++start) {
            int end = start + len - 1;
            // calculate the max # of coins that can be obtained by
            // popping balloons only in the range [start,end].
            // consider all possible choices of final balloon to pop
            int bestCoins = 0;
            for (int final = start; final <= end; ++final) {
                int leftSide = rangeValues[start][final - 1];
                int rightSide = rangeValues[final + 1][end];
                int costForCurrent = nums[start - 1] * nums[final] * nums[end + 1];
                int coins = leftSide + rightSide + costForCurrent;
                if (coins > bestCoins) {
                    bestCoins = coins;
                }
            }
            rangeValues[start][end] = bestCoins;
        }
    }
    return rangeValues[1][N];

}

int getScoreForPoppingBalloons(vector<int> &balloons) {
    int n = balloons.size();
    vector<vector<int>> dp(n + 2, vector<int>(n + 2));

    for (int subArraySize = 1; subArraySize <= n; ++subArraySize) {
        for (int subArrayStart = 0; subArrayStart <= n - subArraySize; ++subArrayStart) {
            int subArrayEnd = subArrayStart + subArraySize - 1;
            for (int splitPoint = subArrayStart; splitPoint < subArrayEnd; ++splitPoint) {

            }
        }
    }

    return dp[0].back();
}

void testBalloonPopping() {
    vector<int> test = {3, 1, 5, 8};
    cout << tempAnswer(test) << endl;
}
