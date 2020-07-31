//
// Created by Tharuka Devendra on 31/07/2020.
//

#include <iostream>
#include "LongestCommonSubString.h"
#include "string"
#include "vector"

using namespace std;

class LongestCommonSubString {
    string txt1;
    string txt2;
    vector<vector<int>> dp;
public:
    LongestCommonSubString(string &txt1, string &txt2) : txt1(txt1), txt2(txt2),
                                                         dp(txt1.size(), vector<int>(txt2.size(), 0)) {}

    int topDown(int i, int j) {
        if (i >= txt1.size() || j >= txt2.size()) {
            return 0;
        }

        if (dp[i][j] != 0) {
            return dp[i][j];
        }

        int score;
        if (txt1[i] == txt2[j]) {
            int move = topDown(i + 1, j + 1);
            score = move + 1;
        } else {
            int moveOne = topDown(i + 1, j);
            int moveTwo = topDown(i, j + 1);
            score = max(moveOne, moveTwo);
        }

        dp[i][j] = score;
        return score;
    }

    int bottomUp() {
        dp.resize(txt1.size()+1, vector<int>(txt2.size()+1, 0));

        for (int i = 1; i <= txt1.size(); ++i) {
            int score = 0;
            for (int j = 1; j <= txt2.size(); ++j) {
                if (txt1[i-1] == txt2[j-1]) {
                    score = dp[i-1][j-1] + 1;
                } else {
                    score = max(dp[i-1][j], dp[i][j-1]);
                }
                dp[i][j] = score;
            }
        }
        return dp.back().back();
    }
};


void testLongestCommonSubString() {
    string txt1 = "AGGTAB";
    string txt2 = "GXTXAYB";
    auto solution = make_unique<LongestCommonSubString>(txt1, txt2);
    assert(solution->topDown(0, 0) == 4);
    auto solution1 = make_unique<LongestCommonSubString>(txt1, txt2);
    assert(solution1->bottomUp() == 4);
}