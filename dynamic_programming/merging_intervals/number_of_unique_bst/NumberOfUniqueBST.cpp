//
// Created by Tharuka Devendra on 18/09/2020.
//

#include "NumberOfUniqueBST.h"
#include "iostream"
#include "vector"
#include "unordered_set"

using namespace std;


int memo(int numberLeft, vector<int> &cache) {
    if (numberLeft == 0) {
        return 1;
    }

    if (cache[numberLeft] != 0) {
        return cache[numberLeft];
    }
    int answer = 0;
    for (int nextParentNode = 1; nextParentNode <= numberLeft; ++nextParentNode) {
        int left = memo(nextParentNode - 1, cache);
        int right = memo(numberLeft - nextParentNode, cache);
        answer += (left * right);
    }
    return answer;
}


int getNumberOfUniqueBSTTopDown(int n) {
    vector<int> cache(n);
    return memo(n, cache);
}

int getNumberOfUniqueBSTBottomUp(int n) {
    vector<int> dp(n);
    dp[0] = 1;
    dp[1] = 1;
    for (int subArraySize = 2; subArraySize <= n; ++subArraySize) {
        for (int parent = 1; parent <= subArraySize; ++parent) {
            int left = dp[parent-1];
            int right = dp[subArraySize-parent];
            dp[subArraySize-1] += left * right;
        }
    }
    return dp.back();
}

void testNumberOfUniqueBST() {
    assert(getNumberOfUniqueBSTTopDown(3) == 14);
    assert(getNumberOfUniqueBSTBottomUp(3) == 14);
}
