//
// Created by Tharuka Devendra on 05/06/2020.
//

#include "BubbleSort.h"
#include "../../Utils.h"
#include "vector"

using namespace std;

void bubbleSort(vector<int> &arr) {
    for (int endPosition = (int) arr.size() - 1; endPosition >= 0; --endPosition) {
        for (int i = 0; i < endPosition - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    }
}

void testBubbleSort() {
    vector<int> test = {2, 9, 6, 2, 3, 10};
    bubbleSort(test);

    Utils::printArr(test);
}
