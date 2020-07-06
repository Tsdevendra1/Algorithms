//
// Created by Tharuka Devendra on 21/06/2020.
//

#include <numeric>
#include "SlidingWindow.h"
#include "vector"
using namespace std;

int maxSlidingWindow(vector<int> &array, int subArraySize){
    int maxSubArraySum = INT_MIN;

    int windowSum = accumulate(array.begin(), array.begin()+subArraySize, 0);
    maxSubArraySum = windowSum;
    for (int i=0; i<array.size()-subArraySize; ++i) {
        int startIndex = i;
        int endIndex = i+subArraySize;
        windowSum = windowSum - array[startIndex] + array[endIndex];
        maxSubArraySum = max(maxSubArraySum, windowSum);
    }
    return maxSubArraySum;
}

void testSlidingWindow(){
    vector<int> test = {1,2,3,4,5,6};
    int maxSubArray = maxSlidingWindow(test, 1);
    assert(maxSubArray == 6);
    maxSubArray = maxSlidingWindow(test, 2);
    assert(maxSubArray == 11);
}