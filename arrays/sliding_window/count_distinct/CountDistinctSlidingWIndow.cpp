//
// Created by Tharuka Devendra on 27/07/2020.
//

#include "CountDistinctSlidingWIndow.h"
#include "vector"
#include "unordered_map"
#include "iostream"
#include "unordered_set"

using namespace std;

vector<int> countDistinctSlidingWithoutHashing(vector<int> &array, int windowSize) {
    // n*windowSize * windowSize time complexity;
    vector<int> numDistinctForEachWindow;
    for (int windowStart = 0; windowStart <= array.size() - windowSize; ++windowStart) {
        int windowEndPlusOne = windowStart + windowSize;
        int numDistinct = 1;
        for (int i = windowStart + 1; i < windowEndPlusOne; ++i) {
            int j;
            for (j = windowStart; j < i; ++j) {
                if (array[j] == array[i]) {
                    break;
                }
            }
            if (j == i) {
                ++numDistinct;
            }
        }
        numDistinctForEachWindow.push_back(numDistinct);
    }
    return numDistinctForEachWindow;
}

void countDistinctSlidingWithSorting(vector<int> &array, int windowSize) {
    // this is same as previous but using the sorted version for the sub arrays
    // n*klogk

}

vector<int> countDistinctSlidingWithHash(vector<int> &array, int windowSize) {
    vector<int> numDistinctForEachWindow;
    for (int windowStart = 0; windowStart <= array.size() - windowSize; ++windowStart) {
        unordered_set<int> unique;
        for (int i = windowStart; i < windowStart + windowSize; ++i) {
            unique.insert(array[i]);
        }
        numDistinctForEachWindow.push_back(unique.size());
    }
    return numDistinctForEachWindow;
}

vector<int> countDistinctOptimal(vector<int> &array, int windowSize) {
    unordered_map<int, int> numCount;
    unordered_set<int> uniqueTracker;

    vector<int> result;
    for (int i = 0; i < windowSize; ++i) {
        int value = array[i];
        ++numCount[value];
        uniqueTracker.insert(value);
    }

    result.push_back(uniqueTracker.size());

    for (int i = 1; i <= array.size() - windowSize; ++i) {
        int beingRemoved = array[i - 1];
        int beingAdded = array[i + windowSize - 1];

        if (numCount[beingRemoved] == 1) {
            uniqueTracker.erase(beingRemoved);
        }
        --numCount[beingRemoved];

        uniqueTracker.insert(beingAdded);
        ++numCount[beingAdded];

        result.push_back(uniqueTracker.size());
    }

    return result;
}

vector<int> countDistinctOptimalDifferentApproach(vector<int> &array, int windowSize) {
    unordered_map<int, int> numCount;
    int numDistinct = 0;
    vector<int> result;
    for (int i = 0; i < windowSize; ++i) {
        int value = array[i];
        if (numCount[value] == 0){
            ++numDistinct;
        }
        ++numCount[value];
    }

    result.push_back(numDistinct);

    for (int i = windowSize; i < array.size(); ++i) {
       int beingRemoved = array[i-windowSize];
       int beingAdded = array[i];
       if (numCount[beingRemoved] == 1){
           --numDistinct;
       }

       --numCount[beingRemoved];

       if (numCount[beingAdded] == 0){
           ++numDistinct;
       }
       ++numCount[beingAdded];

       result.push_back(numDistinct);

    }
    return result;
}

void testCountDistinctSlidingWindow() {
    vector<int> numbers = {1, 2, 3, 4, 5, 5, 6};
    vector<int> expected = {3, 3, 3, 2, 2};
    assert(countDistinctSlidingWithoutHashing(numbers, 3) == expected);
    assert(countDistinctSlidingWithHash(numbers, 3) == expected);
    vector<int> numbers2 = {1, 2, 1, 3, 4, 2, 3};
    vector<int> expected2 = {3, 4, 4, 3};
    assert(countDistinctSlidingWithoutHashing(numbers2, 4) == expected2);
    assert(countDistinctSlidingWithHash(numbers2, 4) == expected2);
    assert(countDistinctOptimal(numbers2, 4) == expected2);
    assert(countDistinctOptimalDifferentApproach(numbers2, 4) == expected2);

}


