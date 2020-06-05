//
// Created by Tharuka Devendra on 03/06/2020.
//

#include "PancakeSort.h"
#include <vector>
#include <iostream>
#include <stack>
#include <numeric>

using namespace std;


void flipVector(vector<int> &arr, int upTo) {
    int start = 0;
    int end = upTo;
    int temp;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        ++start;
        --end;
    }
}

void pancakeSort(vector<int> &arr) {
    for (int size = arr.size(); size > 1; --size) {
        int positionOfMax = max_element(arr.begin(), arr.begin() + size) - arr.begin();
        int lastIndexOfCurrentSize = size - 1;
        if (positionOfMax != lastIndexOfCurrentSize) {
            flipVector(arr, positionOfMax);
            flipVector(arr, lastIndexOfCurrentSize);
        }
    }
}

void testPancakeSort() {
    vector<int> test = {3, 1, 6, 2, 12};
    pancakeSort(test);
    for (auto i: test) {
        cout << i << endl;
    }
}
