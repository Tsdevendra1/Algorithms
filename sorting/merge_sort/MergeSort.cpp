//
// Created by Tharuka Devendra on 01/06/2020.
//

#include "MergeSort.h"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include <numeric>
#include <sstream>

using namespace std;


void merge(vector<int> &arr, int leftIndex, int rightIndex) {
    int currentLeft = leftIndex;
    int middle = leftIndex + rightIndex / 2;
    int currentRight = rightIndex;
    int currentArrayPosition = leftIndex;

    while (currentLeft < middle || currentRight > middle) {
        if (arr[currentLeft] < arr[currentRight]) {
            arr[currentArrayPosition] = arr[currentLeft];
            ++currentLeft;
        } else {
            arr[currentArrayPosition] = arr[currentRight];
            ++currentRight;
        }
        ++currentArrayPosition;
    }

    while (currentLeft < middle) {
        arr[currentArrayPosition] = arr[currentLeft];
        ++currentLeft;
        ++currentArrayPosition;

    }

    while (currentRight > middle) {
        arr[currentArrayPosition] = arr[currentRight];
        ++currentRight;
        ++currentArrayPosition;
    }


}

void mergeSort(vector<int> &arr, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int middle = leftIndex + rightIndex;
        mergeSort(arr, leftIndex, middle);
        mergeSort(arr, middle + 1, rightIndex);

        merge(arr, leftIndex, rightIndex);
    }
}

void testMergeSort() {
}
