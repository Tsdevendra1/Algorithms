//
// Created by Tharuka Devendra on 21/09/2020.
//

#include "BalloonPopping.h"
#include "vector"
#include "iostream"

using namespace std;

int memo(int leftSideBalloon, int rightSideBalloon, vector<int> &balloons, vector<vector<int>> &dp) {

    if (rightSideBalloon - leftSideBalloon == 1) {
        return 0;
    }

    if (rightSideBalloon < leftSideBalloon) {
        return 0;
    }

    int cachedValue = dp[leftSideBalloon][rightSideBalloon];
    if (cachedValue != 0) {
        return cachedValue;
    }

    int answer = INT_MIN;
    for (int chosenBalloon = leftSideBalloon + 1; chosenBalloon < rightSideBalloon; ++chosenBalloon) {
        int maxScoreToRemoveLeft = memo(leftSideBalloon, chosenBalloon, balloons, dp);
        int maxScoreToRemoveRight = memo(chosenBalloon, rightSideBalloon, balloons, dp);
        int scoreForCurrent = balloons[leftSideBalloon] * balloons[chosenBalloon] * balloons[rightSideBalloon];
        int score = scoreForCurrent + maxScoreToRemoveLeft + maxScoreToRemoveRight;
        answer = max(answer, score);
    }

    dp[leftSideBalloon][rightSideBalloon] = answer;
    return answer;
}

int getScoreForPoppingBalloonsTopDown(vector<int> &balloons) {
    balloons.insert(balloons.begin(), 1);
    balloons.insert(balloons.end(), 1);
    vector<vector<int>> dp(balloons.size(), vector<int>(balloons.size(), 0));
    int answer = memo(0, (int) balloons.size() - 1, balloons, dp);
    return answer;
}

int getScoreForPoppingBalloonsBottomUp(vector<int> &balloons) {
    balloons.insert(balloons.begin(), 1);
    balloons.insert(balloons.end(), 1);
    vector<vector<int>> dp(balloons.size(), vector<int>(balloons.size()));
    int n = balloons.size();
    for (int removeArraySize = 3; removeArraySize <= n; ++removeArraySize) {
        for (int startPosition = 0; startPosition <= n - removeArraySize; ++startPosition) {
            int endPosition = startPosition + removeArraySize - 1;
            dp[startPosition][endPosition] = INT_MIN;
            for (int chosenBalloon = startPosition + 1; chosenBalloon < endPosition; ++chosenBalloon) {

                int maxRemoveLeft = dp[startPosition][chosenBalloon];
                int maxRemoveRight = dp[chosenBalloon][endPosition];

                int scoreForCurrent = balloons[startPosition] * balloons[chosenBalloon] * balloons[endPosition];

                int previous = dp[startPosition][endPosition];
                int score = scoreForCurrent + maxRemoveLeft + maxRemoveRight;

                dp[startPosition][endPosition] = max(previous, score);
            }
        }
    }
    return dp[0][n - 1];
}

void testBalloonPopping() {
    vector<int> test = {3, 5, 8};
    assert(getScoreForPoppingBalloonsTopDown(test) == 152);
    vector<int> test2 = {3, 5, 8};
    assert(getScoreForPoppingBalloonsBottomUp(test2) == 152);
}
