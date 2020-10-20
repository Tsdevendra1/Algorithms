//
// Created by Tharuka Devendra on 13/10/2020.
//

#include "ShortestCommonSuperSequence.h"
#include "string"
#include "vector"
#include "iostream"

using namespace std;

int memo(int stringOnePosition, int stringTwoPosition, string &stringOne, string &stringTwo, vector<vector<int>> &dp) {
    if (stringOnePosition < 0 || stringTwoPosition < 0) {
        return 0;
    }

    if (dp[stringOnePosition][stringTwoPosition] != 0) {
        return dp[stringOnePosition][stringTwoPosition];
    }

    int score;
    if (stringOne[stringOnePosition] == stringTwo[stringTwoPosition]) {
        score = memo(stringOnePosition - 1, stringTwoPosition - 1, stringOne, stringTwo, dp) + 1;
    } else {
        int moveInOne = memo(stringOnePosition - 1, stringTwoPosition, stringOne, stringTwo, dp);
        int moveInTwo = memo(stringOnePosition, stringTwoPosition - 1, stringOne, stringTwo, dp);
        score = max(moveInOne, moveInTwo);
    }

    dp[stringOnePosition][stringTwoPosition] = score;
    return score;
}

vector<vector<int>> getLongestCommonSubsequenceDpMatrix(string &stringOne, string &stringTwo) {
    int n = stringOne.length();
    int m = stringTwo.length();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    memo(n - 1, m - 1, stringOne, stringTwo, dp);
    return dp;
}

string getShortestCommonSuperSequence(string &stringOne, string &stringTwo) {
    auto dpMatrix = getLongestCommonSubsequenceDpMatrix(stringOne, stringTwo);

    int stringOnePosition = dpMatrix.size() - 1;
    int stringTwoPosition = dpMatrix[0].size() - 1;

    string answer;
    while (stringOnePosition >= 0 && stringTwoPosition >= 0) {
        int moveOne = stringOnePosition > 0 ? dpMatrix[stringOnePosition - 1][stringTwoPosition] : 0;
        int moveTwo = stringTwoPosition > 0 ? dpMatrix[stringOnePosition][stringTwoPosition - 1] : 0;
        if (stringOne[stringOnePosition] == stringTwo[stringTwoPosition]) {
            answer += stringOne[stringOnePosition];
            --stringOnePosition;
            --stringTwoPosition;
        } else if (moveTwo > moveOne) {
            answer += stringTwo[stringTwoPosition];
            --stringTwoPosition;
        } else {
            answer += stringOne[stringOnePosition];
            --stringOnePosition;
        }
    }

    while (stringTwoPosition >= 0) {
        answer += stringTwo[stringTwoPosition];
        --stringTwoPosition;
    }

    while (stringOnePosition >= 0) {
        answer += stringOne[stringOnePosition];
        --stringOnePosition;
    }

    reverse(answer.begin(), answer.end());
    return answer;
}

string shortestCommonSuperSequenceAlternate() {
    // Look at getting lcs directly and going through it;

}

void testShortestCommonSuperSequence() {

    string txt1 = "bbbaaaba";
    string txt2 = "bbababbb";

    cout << getShortestCommonSuperSequence(txt1, txt2) << endl;
}
