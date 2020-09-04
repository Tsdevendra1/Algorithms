//
// Created by Tharuka Devendra on 03/08/2020.
//

#include <iostream>
#include "LongestCommonSubString.h"
#include "string"
#include "vector"
#include "unordered_map"

using namespace std;

class TopdownLongestCommonSubstring {
    vector<int> A;
    vector<int> B;
    vector<vector<int>> dp;
    int answer = 0;
public:
    int topdownLongestCommonSubstring(vector<int> &C, vector<int> &D) {
        dp.resize(C.size(), vector<int>(D.size(), -1));
        A = C;
        B = D;
        memo(A.size() - 1, B.size() - 1);
        return answer;
    }

    int memo(int one, int two) {
        if (one < 0 || two < 0)
            return 0;

        if (dp[one][two] != -1) {
            return dp[one][two];
        }

        int currentBest = 0;
        if (A[one] == B[two]) {
            currentBest = 1 + memo(one - 1, two - 1);
        }
        dp[one][two] = currentBest;
        memo(one - 1, two);
        memo(one, two - 1);
        answer = max(answer, dp[one][two]);
        return dp[one][two];
    }
};

class LongestCommonSubString {
    string txt1;
    string txt2;
    vector<vector<unordered_map<int, int>>> dp;
public:
    LongestCommonSubString(string &txt1, string &txt2) : txt1(txt1), txt2(txt2),
                                                         dp(txt1.size(), vector<unordered_map<int, int>>(txt2.size())) {
    }

    // this version doesn't actually work on leetcode, it timesout
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
    vector<int> test1 = {1, 2, 3, 4, 5, 6};
    vector<int> test2 = {2, 1, 4, 3, 4, 5, 6};

    auto solution1 = make_unique<LongestCommonSubString>(txt1, txt2);
    auto solution2 = make_unique<LongestCommonSubString>(txt1, txt2);
    auto solution3 = make_unique<TopdownLongestCommonSubstring>();
    assert(solution3->topdownLongestCommonSubstring(test1, test2) == 4);
    assert(solution1->topDown(0, 0, 0) == 6);
    assert(solution2->bottomUp() == 6);
}
