//
// Created by Tharuka Devendra on 05/06/2020.
//

#include "InsertionSort.h"
#include "../../Utils.h"
#include "vector"

using namespace std;

void insertionSort(vector<int> &arr) {
    vector<int> subArray;
    for (int current : arr) {
        subArray.push_back(current);
        int index = (int) subArray.size() - 1;
        while (index > 0 && subArray[index - 1] > current) {
            int temp = subArray[index - 1];
            subArray[index - 1] = subArray[index];
            subArray[index] = temp;
            --index;
        }

    }
    arr = subArray;
}

void testInsertionSort() {
    vector<int> test = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    insertionSort(test);
    Utils::printArr(test);
}
