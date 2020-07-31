//
// Created by Tharuka Devendra on 31/07/2020.
//

#include <iostream>
#include "LongestCommonSub.h"
#include "string"
#include "vector"

using namespace std;

class LongestCommonSub {
    string txt1;
    string txt2;
    vector<vector<int>> dp;
public:
    LongestCommonSub(string &txt1, string &txt2) : txt1(txt1), txt2(txt2),
                                                   dp(txt1.size(), vector<int>(txt2.size(), 0)) {}

    int solve(int i, int j) {
        if (i >= txt1.size() || j >= txt2.size()) {
            return 0;
        }

        if (dp[i][j] != 0) {
            return dp[i][j];
        }

        int score;
        if (txt1[i] == txt2[j]) {
            int positionOne = solve(i + 1, j + 1);
            score = positionOne + 1;
        } else {
            int positionOne = solve(i + 1, j);
            int positionTwo = solve(i, j + 1);
            score = max(positionOne, positionTwo);
        }

        dp[i][j] = score;
        return score;
    }
};


void testLongestCommonSub() {
    string txt1 = "AGGTAB";
    string txt2 = "GXTXAYB";
    auto solution = make_unique<LongestCommonSub>(txt1, txt2);
    assert(solution->solve(0, 0) == 4);
}