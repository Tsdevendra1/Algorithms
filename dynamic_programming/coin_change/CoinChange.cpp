//
// Created by Tharuka Devendra on 26/08/2020.
//

#include "CoinChange.h"
#include "vector"
#include "iostream"

using namespace std;


int numberOfCoinsBottomUp(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);

    dp[0] = 0;
    for (int coin: coins) {
        if (coin < dp.size()) {
            dp[coin] = coin;
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
    int amount = 1;
    assert(numberOfCoinsBottomUp(coins, amount) == 3);
}