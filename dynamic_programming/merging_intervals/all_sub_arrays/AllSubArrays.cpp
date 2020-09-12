//
// Created by Tharuka Devendra on 12/09/2020.
//

#include "AllSubArrays.h"
#include "vector"
#include "iostream"

using namespace std;

void dfsShrinking(int startOfSubArray, int endOfSubArray, vector<int> &array, vector<vector<int>> &answer,
                  vector<vector<bool>> &seen) {
    if (endOfSubArray < startOfSubArray) {
        return;
    }

    if (seen[startOfSubArray][endOfSubArray]) {
        return;
    }

    seen[startOfSubArray][endOfSubArray] = true;
    answer.emplace_back(array.begin() + startOfSubArray, array.begin() + endOfSubArray + 1);
    dfsShrinking(startOfSubArray + 1, endOfSubArray, array, answer, seen);
    dfsShrinking(startOfSubArray, endOfSubArray - 1, array, answer, seen);
}

vector<vector<int>> getAllSubArraysTopDownShrinking(vector<int> &array) {
    vector<vector<int>> answer;
    vector<vector<bool>> seen(array.size(), vector<bool>(array.size(), false));
    dfsShrinking(0, array.size() - 1, array, answer, seen);
    return answer;
}


void dfsExpanding(int startOfSubArray, int endOfSubArray, vector<int> &array, vector<vector<int>> &answer) {

    if (endOfSubArray >= array.size()) {
        return;
    }

    if (endOfSubArray < startOfSubArray) {
        dfsExpanding(0, endOfSubArray + 1, array, answer);
    } else {
        answer.emplace_back(array.begin() + startOfSubArray, array.begin() + endOfSubArray + 1);
        dfsExpanding(startOfSubArray + 1, endOfSubArray, array, answer);
    }

}


vector<vector<int>> getAllSubArraysTopDownExpanding(vector<int> &array) {
    vector<vector<int>> answer;
    dfsExpanding(0, 0, array, answer);
    return answer;
}

vector<vector<int>> getAllSubArrays(vector<int> &array) {

    vector<vector<int>> answer;
    // the first two outer for loops gives the combos of the start and end of different size sub arrays
    for (int subArraySize = 1; subArraySize <= array.size(); ++subArraySize) {
        for (int subArrayStart = 0; subArrayStart <= array.size() - subArraySize; ++subArrayStart) {
            // minus one because the start position is included hence the last position isn't to get the correct number
            int subArrayEndPosition = (subArrayStart + subArraySize) - 1;
            answer.emplace_back(array.begin() + subArrayStart, array.begin() + subArrayEndPosition + 1);
        }
    }
    return answer;

}

void testAllSubArrays() {
    vector<int> test = {6, 2, 4};
    auto answer = getAllSubArrays(test);
    auto answer2 = getAllSubArraysTopDownShrinking(test);
    auto answer3 = getAllSubArraysTopDownExpanding(test);
    assert(answer.size() == 6);
    assert(answer2.size() == 6);
    assert(answer3.size() == 6);
}
