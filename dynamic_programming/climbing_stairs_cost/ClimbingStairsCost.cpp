//
// Created by Tharuka Devendra on 24/08/2020.
//

#include "ClimbingStairsCost.h"
#include "vector"

using namespace std;

int dfs(int currentStep, vector<int> &costs, vector<int> &dp) {

    if (currentStep < 0) {
        return 0;
    }

    if (dp[currentStep]) {
        return dp[currentStep];
    }

    int costForCurrentStep = currentStep == costs.size() ? 0 : costs[currentStep];
    int stepOne = dfs(currentStep - 1, costs, dp) + costForCurrentStep;
    int stepTwo = dfs(currentStep - 2, costs, dp) + costForCurrentStep;

    dp[currentStep] = min(stepOne, stepTwo);
    return dp[currentStep];
}

int minCostClimbingStairsTopDown(vector<int> &costs) {
    vector<int> dp(costs.size() + 1);
    return dfs(costs.size(), costs, dp);
}

int minCostClimbingStairsBottomUp(vector<int> &cost) {
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
    int cost = minCostClimbingStairsBottomUp(costs);
    int costTopDown = minCostClimbingStairsTopDown(costs);
    assert(cost == 2);
    assert(cost == costTopDown);
}
