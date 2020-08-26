//
// Created by Tharuka Devendra on 26/08/2020.
//

#include "CoinChange.h"
#include "vector"
#include "iostream"

using namespace std;

int numberOfCoinsDfs(int currentTotal, vector<int> &coins, int amount, vector<int> &dp) {
    if (currentTotal == 0) {
        return 0;
    }

    if (currentTotal < 0) {
        return INT_MAX;
    }

    if (dp[currentTotal]) {
        return dp[currentTotal];
    }

    int numCoins = INT_MAX;
    for (int coin: coins) {
        int numberOfCoinsForPreviousTotal = numberOfCoinsDfs(currentTotal - coin, coins, amount, dp);
        if (numberOfCoinsForPreviousTotal != INT_MAX) {
            numCoins = min(numCoins, numberOfCoinsForPreviousTotal + 1);
        }
    }
    dp[currentTotal] = numCoins;
    return dp[currentTotal];
}

int numberOfCoinsTopDown(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, 0);
    for (int coin: coins) {
        if (coin < dp.size()) {
            dp[coin] = 1;
        }
    }
    int answer = numberOfCoinsDfs(amount, coins, amount, dp);
    return answer == INT_MAX ? -1 : answer;
}

int numberOfCoinsBottomUp(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);

    dp[0] = 0;
    for (int coin: coins) {
        if (coin < dp.size()) {
            dp[coin] = 1;
        }
    }

    for (int currentAmount = 1; currentAmount <= amount; ++currentAmount) {
        for (int coin: coins) {
            int previousCoinTotal = currentAmount - coin;
            if (0 <= previousCoinTotal && dp[previousCoinTotal] != INT_MAX) {
                dp[currentAmount] = min(dp[previousCoinTotal] + 1, dp[currentAmount]);
            }
        }
    }
    return (dp.back() == INT_MAX) ? -1 : dp.back();

}

void testCoinChange() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    assert(numberOfCoinsBottomUp(coins, amount) == 3);
    assert(numberOfCoinsTopDown(coins, amount) == 3);
}