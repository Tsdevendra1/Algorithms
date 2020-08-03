//
// Created by Tharuka Devendra on 03/08/2020.
//

#include <iostream>
#include "LongestCommonSubString.h"
#include "string"
#include "vector"
#include "unordered_map"

using namespace std;

class LongestCommonSubString {
    string txt1;
    string txt2;
    vector<vector<unordered_map<int, int>>> dp;
public:
    LongestCommonSubString(string &txt1, string &txt2) : txt1(txt1), txt2(txt2),
                                                         dp(txt1.size(), vector<unordered_map<int, int>>(txt2.size())) {
    }

    int topDown(int i, int j, int currentCount) {
        if (i >= txt1.size() || j >= txt2.size()) {
            return currentCount;
        }

        if (dp[i][j][currentCount] != 0) {
            return dp[i][j][currentCount];
        }

        int score = currentCount;
        if (txt1[i] == txt2[j]) {
            score = max(score, topDown(i + 1, j + 1, currentCount + 1));
        }
        int moveOne = topDown(i + 1, j, 0);
        int moveTwo = topDown(i, j + 1, 0);
        score = max(score, max(moveOne, moveTwo));
        dp[i][j][currentCount] = score;
        return score;
    }

    int bottomUp() {
        vector<vector<int>> localDp(txt1.size(), vector<int>(txt2.size()));

        int maxAmount = INT_MIN;
        for (int i = 0; i < txt1.size(); ++i) {
            for (int j = 0; j < txt2.size(); ++j) {
                if (txt1[i] == txt2[j]) {
                    int previousScore = (i >= 1 && j >= 1) ? localDp[i - 1][j - 1] : 0;
                    int score = 1 + previousScore;
                    localDp[i][j] = score;
                    maxAmount = max(maxAmount, score);
                }
            }
        }

        return maxAmount;
    }
};


void testLongestCommonSubString() {
    string txt1 = "zxabcdezy";
    string txt2 = "yzabcdezx";

    auto solution1 = make_unique<LongestCommonSubString>(txt1, txt2);
    auto solution2 = make_unique<LongestCommonSubString>(txt1, txt2);

    assert(solution1->topDown(0, 0, 0) == 6);
    assert(solution2->bottomUp() == 6);
}
