//
// Created by Tharuka Devendra on 29/07/2020.
//

#include <vector>
#include "LongestPalindromSubTopDown.h"
#include "string"
#include "iostream"

using namespace std;

class LongestPalindromTopDown {
    vector<vector<int>> dp;
    string original;
    int currentMax = INT_MIN;

public:
    int solve(int x, int y) {
        if (x > y)
            return 0;

        int ret = dp[x][y];

        if (ret != 0) {
            return ret;
        }

        ret = max(solve(x + 1, y), solve(x, y - 1));
        if (original[x] == original[y]) {
            int val = solve(x + 1, y - 1);
            int newRight = (y - 1);
            int newLeft = (x + 1);
            int sizeAfterRemovingCharacters = newRight - newLeft + 1;
            // this makes sense because if the value (which represents the longest palindromic sub string
            if (val >= sizeAfterRemovingCharacters) {
                int addScore = (x == y) ? 1 : 2;
                ret = val + addScore;
                if (ret > currentMax) {
                    currentMax = ret;
                    start = x;
                    end = y;
                }
            }

        }
        dp[x][y] = ret;
        return ret;
    }

    int start;
    int end;
    explicit LongestPalindromTopDown(string &originalString) : original(originalString), dp(originalString.length(),
                                                                                            vector<int>(
                                                                                                    originalString.length())) {};
};

void testLongestPalindromSubTopDown() {
    string str = "abadbbda";
    auto answer = make_unique<LongestPalindromTopDown>(str);
    assert(answer->solve(0, (int) str.size() - 1) == 6);

    string str2 = "forgeeksskeegfor";
    auto answer2 = make_unique<LongestPalindromTopDown>(str2);
    assert(answer2->solve(0, (int) str2.size() - 1) == 10);

    string palindromString = str2.substr(answer2->start, (answer2->end-answer2->start+1));
    assert(palindromString == "geeksskeeg");

}
