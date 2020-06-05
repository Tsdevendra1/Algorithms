//
// Created by Tharuka Devendra on 05/06/2020.
//

#include "QuickSort.h"
#include <vector>
#include "../../Utils.h"

using namespace std;

int getSplitPoint(vector<int> &arr, int left, int right) {
    int currentLeft = left + 1;
    int currentRight = right;
    int pivotValue = arr[left];

    while (true) {
        while (arr[currentLeft] <= pivotValue && currentLeft <= currentRight) {
            ++currentLeft;
        }

        while (arr[currentRight] >= pivotValue && currentRight >= currentLeft) {
            --currentRight;
        }

        if (currentLeft <= currentRight) {
            int temp = arr[currentLeft];
            arr[currentLeft] = arr[currentRight];
            arr[currentRight] = temp;
        } else {
            break;
        }
    }

    arr[left] = arr[currentRight];
    arr[currentRight] = pivotValue;
    return currentRight;
}

void quickSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int split = getSplitPoint(arr, left, right);
        quickSort(arr, left, split - 1);
        quickSort(arr, split + 1, right);
    }
}

void testQuickSort() {
    vector<int> test = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    quickSort(test, 0, (int) test.size() - 1);
    Utils::printArr(test);
};
