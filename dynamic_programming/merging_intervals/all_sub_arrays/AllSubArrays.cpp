//
// Created by Tharuka Devendra on 12/09/2020.
//

#include "AllSubArrays.h"
#include "vector"
#include "iostream"

using namespace std;

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
    assert(answer.size() == 6);
}
