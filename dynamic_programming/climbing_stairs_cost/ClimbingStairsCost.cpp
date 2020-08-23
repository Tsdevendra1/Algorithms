//
// Created by Tharuka Devendra on 24/08/2020.
//

#include "ClimbingStairsCost.h"
#include "vector"

using namespace std;

int minCostClimbingStairs(vector<int> &cost) {
    vector<int> dp(cost.size() + 1);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int step = 2; step <= cost.size(); ++step) {
        int costForStep = (step == cost.size()) ? 0 : cost[step];
        dp[step] = min(dp[step - 1], dp[step - 2]) + costForStep;
    }
    return dp.back();
}

void testClimbingStairsCost() {
    vector<int> costs = {1, 100, 1};
    int cost = minCostClimbingStairs(costs);
    assert(cost == 2);
}
