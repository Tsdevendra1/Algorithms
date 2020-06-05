//
// Created by Tharuka Devendra on 05/06/2020.
//

#include "SelectionSort.h"
#include "../../Utils.h"

#include "vector"

using namespace std;

void selectionSort(vector<int> &arr) {
    for (int endPosition = (int) arr.size() - 1; endPosition >= 0; --endPosition) {
        int positionOfMax = 0;
        for (int i = 0; i < endPosition+1; ++i) {
            if (arr[i] > arr[positionOfMax]) {
                positionOfMax = i;
            }
        }
        int temp = arr[positionOfMax];
        arr[positionOfMax] = arr[endPosition];
        arr[endPosition] = temp;

    }
}

void testSelectionSort() {
    vector<int> test = {1, 10, 5, 11, 9, 3, 7};
    selectionSort(test);
    Utils::printArr(test);

}
