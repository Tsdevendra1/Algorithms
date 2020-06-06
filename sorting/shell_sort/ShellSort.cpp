//
// Created by Tharuka Devendra on 05/06/2020.
//

#include "ShellSort.h"
#include "../../Utils.h"
#include "vector"


using namespace std;

void insertionSortGap(vector<int> &arr, int start, int gap) {

    for (int i = start; i < arr.size(); i += gap) {
        int current = arr[i];
        int index = i;
        while (index >= gap && arr[index - gap] > current) {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index -= gap;
        }
    }

}

void shellSort(vector<int> &arr) {
    int size = (int) arr.size() / 2;
    while (size > 0) {
        for (int startPosition = 0; startPosition < size; ++startPosition) {
            insertionSortGap(arr, startPosition, size);
        }
        size /= 2;
    }
}


void testShellSort() {
    vector<int> test = {4, 2, 6, 2, 9, 1};
    shellSort(test);
    Utils::printArr(test);
}
