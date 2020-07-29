//
// Created by Tharuka Devendra on 27/07/2020.
//

#include "AtmostKDistinct.h"
#include "vector"
#include "unordered_set"
#include "unordered_map"

using namespace std;

int numSubArraysDistinctUpToK(vector<int> &array, int windowSize) {
    int numSubarrays = 0;
    int left = 0;
    int right = 0;
    unordered_map<int, int> inCurrentWindow;

    while (right < array.size()) {
        // keep track of new element
        ++inCurrentWindow[array[right]];

        // need to decrease the window if num of distinct elements is too much
        while (left < right && inCurrentWindow.size() > windowSize){
            int value = array[left];
            --inCurrentWindow[value];
            if (inCurrentWindow[value] == 0) {
                inCurrentWindow.erase(value);
            }
            ++left;
        }
        // overall loop increases the size of the window
        int sizeOfWindow = right-left + 1;
        numSubarrays += sizeOfWindow;
        ++right;
    }
    return numSubarrays;
}

int getNumberOfSubarrayWithKDistinct(vector<int> &array, int windowSize) {
    // the difference will be the number of subarrays with exactly K different numbers
    return numSubArraysDistinctUpToK(array, windowSize) - numSubArraysDistinctUpToK(array, windowSize - 1);
}

void testAtmostKDistinct() {
    vector<int> test = {1, 2, 1, 2, 3};
    int windowSize = 2;
    assert(getNumberOfSubarrayWithKDistinct(test, 2) == 7);
};