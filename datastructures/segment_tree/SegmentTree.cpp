//
// Created by Tharuka Devendra on 01/06/2020.
//


#include "SegmentTree.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;


void _updateValueUtil(vector<int> &segTree, int start, int end, int index, int diff, int currentIndex) {
    if (start > index || end < index) {
        return;
    }

    segTree[currentIndex] = segTree[currentIndex] + diff;
    if (start != end) {
        int middleIndex = (start + end) / 2;
        _updateValueUtil(segTree, start, middleIndex, index, diff, 2 * currentIndex + 1);
        _updateValueUtil(segTree, middleIndex + 1, end, index, diff, 2 * currentIndex + 2);
    }
}

void _updateValue(vector<int> &originalArray, vector<int> &segTree, int index, int value) {
    if (index < 0 || index > originalArray.size() - 1) {
        cout << "Invalid Input";
        return;
    }

    int diff = value - originalArray[index];

    originalArray[index] = value;

    _updateValueUtil(segTree, 0, originalArray.size() - 1, index, diff, 0);
}

int
_getSumUtil(vector<int> &segTree, int trueArrayStart, int trueArrayEnd, int queryStart, int queryEnd,
            int currentIndex) {
    if (queryStart <= trueArrayStart && trueArrayEnd <= queryEnd) {
        return segTree[currentIndex];
    }

    if (queryEnd < trueArrayStart || trueArrayEnd < queryStart) {
        return 0;
    }

    int mid = (trueArrayStart + trueArrayEnd) / 2;
    return _getSumUtil(segTree, trueArrayStart, mid, queryStart, queryEnd, 2 * currentIndex + 1) +
           _getSumUtil(segTree, mid + 1, trueArrayEnd, queryStart, queryEnd, 2 * currentIndex + 2);

}

int _getSum(vector<int> &segTree, int originalArraySize, int start, int end) {
    if (start < 0 || end < 0 || start >= originalArraySize || start > end) {
        return -1;
    }

    return _getSumUtil(segTree, 0, originalArraySize - 1, start, end, 0);
}

int constructSegTreeUtil(vector<int> &actualArray, vector<int> &segTree, int start, int end, int currentIndex) {
    if (start == end) {
        segTree[currentIndex] = actualArray[start];
        return actualArray[start];
    }

    int middleIndex = (start + end) / 2;
    segTree[currentIndex] = constructSegTreeUtil(actualArray, segTree, start, middleIndex, currentIndex * 2 + 1) +
                            constructSegTreeUtil(actualArray, segTree, middleIndex + 1, end, currentIndex * 2 + 2);

    return segTree[currentIndex];
}


vector<int> constructSegmentTree(vector<int> &arr) {

    int segTreeSize;
    int arraySize = arr.size();

    // This is if tree height starts at 0 for node 1
    int treeHeight = floor(log2(arraySize));
    // treeHeight + 1 is effectively same as ceil but makes more sense in my mind like this. This is essentially saying
    // we need treeheight + one full level worth of nodes in the max case
    int numberOfNodes = pow(2, treeHeight + 1);
    segTreeSize = (int) (2 * numberOfNodes) - 1;

    vector<int> segmentTree(segTreeSize);

    constructSegTreeUtil(arr, segmentTree, 0, arraySize - 1, 0);

    return segmentTree;
}


void testSegmentTree() {

    vector<int> arr1 = {1, 3, 5, 7, 9, 11};
    int n = arr1.size();


    vector<int> segTree = constructSegmentTree(arr1);
    cout << _getSum(segTree, n, 2, 4) << endl;

    _updateValue(arr1, segTree, 1, 10);

    cout << "Updated sum of values in given range = "
         << _getSum(segTree, n, 1, 3) << endl;
}
