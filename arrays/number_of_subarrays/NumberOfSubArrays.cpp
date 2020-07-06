//
// Created by Tharuka Devendra on 06/07/2020.
//

#include "NumberOfSubArrays.h"
#include "vector"
using namespace std;

int getNumSubArrays(int arraySize) {
    int count = 0;
    // This works by getting the largest size and shrinking to the right
    // e.g {0,1,2}
    // for {0} -> {0} == 1
    // for {0, 1} -> {0, 1}, {1} == 2
    // for {0, 1, 3} -> {0, 1, 2}, {1, 2}, {2} == 3
    // how many positions can you put which goes up to and including from right index to left index index 0, 1, 2
    // e.g for last index 0 == {0,1,2}, index 1 == {1,2} (right to left index) etc...
    // hence total == 6
    for (int subArrayEndIndex=0; subArrayEndIndex < arraySize; ++subArrayEndIndex) {
        int startIndex = 0;
        int endIndex = subArrayEndIndex;
        int subArraySize = endIndex - startIndex + 1;
        count += subArraySize;
    }
    return count;
};
void testNumberOfSubArrays(){
    vector<int> test = {1,2,3};
    int numSubArrays = getNumSubArrays(test.size());
    assert(numSubArrays == 6);
};
