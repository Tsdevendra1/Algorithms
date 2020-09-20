//
// Created by Tharuka Devendra on 19/09/2020.
//

#include "RemovingBoxes.h"
#include "vector"
#include "iostream"

using namespace std;

int memo(int subArrayStart, int subArrayEnd, int numberOfMatchingBoxesBeforeStart, vector<int> &boxes,
         vector<vector<vector<int>>> &dp) {
    if (subArrayEnd < subArrayStart || subArrayStart > subArrayEnd) {
        return 0;
    }

    int dpValue = dp[subArrayStart][subArrayEnd][numberOfMatchingBoxesBeforeStart];
    if (dpValue != 0) {
        return dpValue;
    }

    int currentValue = boxes[subArrayStart];
    int lastMatchingPosition = subArrayStart;
    while (lastMatchingPosition <= subArrayEnd && boxes[lastMatchingPosition] == currentValue) {
        ++lastMatchingPosition;
    }

    int numberOfMatches = lastMatchingPosition - subArrayStart;
    int numberOfMatchesForCurrentValue = numberOfMatchingBoxesBeforeStart + numberOfMatches;
    int score = (int) pow(numberOfMatchesForCurrentValue, 2);
    int newStartPosition = subArrayStart + numberOfMatches;
    int movingForward = memo(newStartPosition, subArrayEnd, 0, boxes, dp);
    int answer = movingForward + score;


    for (int matchingPosition = newStartPosition; matchingPosition <= subArrayEnd; ++matchingPosition) {
        if (boxes[matchingPosition] == currentValue) {
            int inbetweenScore = memo(newStartPosition, matchingPosition - 1, 0, boxes, dp);
            int afterScore = memo(matchingPosition, subArrayEnd, numberOfMatchesForCurrentValue, boxes, dp);
            int scoreForCurrent = inbetweenScore + afterScore;
            answer = max(answer, scoreForCurrent);
        }
    }

    dp[subArrayStart][subArrayEnd][numberOfMatchingBoxesBeforeStart] = answer;
    return answer;
}

int maxScoreFromRemovingBoxes(vector<int> &boxes) {
    int n = boxes.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
    return memo(0, (int) boxes.size() - 1, 0, boxes, dp);
}

void testRemovingBoxes() {
    vector<int> boxes = {1, 3, 2, 2, 2, 3, 4, 3, 1};
    assert(maxScoreFromRemovingBoxes(boxes) == 23);
}
