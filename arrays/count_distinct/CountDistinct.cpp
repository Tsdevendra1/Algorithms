//
// Created by Tharuka Devendra on 27/07/2020.
//

#include "CountDistinct.h"
#include "vector"
#include "unordered_set"
#include "iostream"

using namespace std;

int countDistinctWithoutHashing(vector<int> &array) {
    // this is n^2
    int result = 1;
    for (int i = 1; i < array.size(); ++i) {
        int j;
        for (j = 0; j < i; ++j) {
            if (array[j] == array[i]) {
                break;
            }
        }

        if (j == i) {
            ++result;
        }
    }
    return result;
}

int countDistinctWithSorting(vector<int> &array) {
    // this method is nlogn
    sort(array.begin(), array.end());
    int result = 0;
    for (int i = 0; i < array.size(); ++i) {
        ++result;
        while (array[i] == array[i+1] && i < array.size()){
            ++i;
        }
    }
    return result;
}

int countDistinct(vector<int> &array) {
    // this method is n
    unordered_set<int> uniqueNumbers;
    for (int value:array) {
        uniqueNumbers.insert(value);
    }
    return uniqueNumbers.size();
}

void testCountDistinct() {
    vector<int> numbers = {1, 2, 3, 4, 5, 5, 6};
    assert(countDistinct(numbers) == 6);
    assert(countDistinctWithoutHashing(numbers) == 6);
    assert(countDistinctWithSorting(numbers) == 6);
}