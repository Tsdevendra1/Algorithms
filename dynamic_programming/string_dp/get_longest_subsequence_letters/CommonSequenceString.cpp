//
// Created by Tharuka Devendra on 13/10/2020.
//

#include "CommonSequenceString.h"
#include "string"
#include "iostream"
#include "vector"

using namespace std;

vector<vector<int>> getlongestCommonSubDpMatrix(string &stringOne, string &stringTwo) {
    int n = stringOne.length();
    int m = stringTwo.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char one = stringOne[i];
            char two = stringTwo[j];

            if (one == two) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            } else {
                int previousOne = dp[i + 1][j];
                int previousTwo = dp[i][j + 1];
                dp[i + 1][j + 1] = max(previousOne, previousTwo);
            }
        }
    }
    return dp;
}

string getCommonSequenceString(string &stringOne, string &stringTwo) {
    string answer;
    auto dpMatrix = getlongestCommonSubDpMatrix(stringOne, stringTwo);
    int stringOnePosition = (int) dpMatrix.size() - 1;
    int stringTwoPosition = (int) dpMatrix[0].size() - 1;

    // Remember off by one errors
    while (stringTwoPosition >= 1 && stringOnePosition >= 1) {
        int moveBackwardsInStringTwo = dpMatrix[stringOnePosition][stringTwoPosition - 1];
        int moveBackwardsInStringOne = dpMatrix[stringOnePosition - 1][stringTwoPosition];

        if (stringOne[stringOnePosition - 1] == stringTwo[stringTwoPosition - 1]) {
            answer += stringOne[stringOnePosition - 1];
            --stringOnePosition;
            --stringTwoPosition;
        } else if (moveBackwardsInStringTwo > moveBackwardsInStringOne) {
            --stringTwoPosition;
        } else {
            --stringOnePosition;
        }
    }

    // Since we're going backwards in the matrix have to reverse the answer;
    reverse(answer.begin(), answer.end());
    return answer;
}

void testCommonSequenceString() {
    string txt1 = "AGGTAB";
    string txt2 = "GXTXAYB";
    cout << getCommonSequenceString(txt1, txt2) << endl;
}
