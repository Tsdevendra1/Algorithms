//
// Created by Tharuka Devendra on 01/06/2020.
//

#include "MergeSort.h"

#include <iostream>
#include <vector>

using namespace std;


void merge(vector<int> &arr, int leftIndex, int rightIndex) {
    int middle = (leftIndex + rightIndex) / 2;
    int currentRight = 0;
    int currentLeft = 0;
    int currentArrayPosition = leftIndex;
    vector<int> leftArray;
    vector<int> rightArray;

    for (int i = leftIndex; i <= middle; ++i) {
        leftArray.push_back(arr[i]);
    }

    for (int i = middle + 1; i <= rightIndex; ++i) {
        rightArray.push_back(arr[i]);
    }

    while (currentLeft < leftArray.size() && currentRight < rightArray.size()) {
        if (leftArray[currentLeft] < rightArray[currentRight]) {
            arr[currentArrayPosition] = leftArray[currentLeft];
            ++currentLeft;
        } else {
            arr[currentArrayPosition] = rightArray[currentRight];
            ++currentRight;
        }
        ++currentArrayPosition;
    }

    while (currentLeft < leftArray.size()) {
        arr[currentArrayPosition] = leftArray[currentLeft];
        ++currentLeft;
        ++currentArrayPosition;

    }

    while (currentRight < rightArray.size()) {
        arr[currentArrayPosition] = rightArray[currentRight];
        ++currentRight;
        ++currentArrayPosition;
    }


}

void mergeSort(vector<int> &arr, int leftIndex, int rightIndex) {
    cout << leftIndex << " " << rightIndex << endl;
    if (leftIndex < rightIndex) {
        int middle = (leftIndex + rightIndex) / 2;
        mergeSort(arr, leftIndex, middle);
        mergeSort(arr, middle + 1, rightIndex);

        merge(arr, leftIndex, rightIndex);
    }
}

void printArrR(vector<int> &arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

void testMergeSort() {
    vector<int> arr = {4, 2, 15, 8, 1};
    mergeSort(arr, 0, (int) arr.size() - 1);
    printArrR(arr);

}
