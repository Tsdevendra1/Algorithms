//
// Created by Tharuka Devendra on 27/07/2020.
//

#include "CountDistinct.h"
#include "vector"
#include "unordered_set"

using namespace std;


int countDistinct(vector<int> &array) {
    unordered_set<int> uniqueNumbers;
    for (int value:array) {
        uniqueNumbers.insert(value);
    }
    return uniqueNumbers.size();
}

void testCountDistinct() {
    vector<int> numbers = {1,2,3,4,5,5,6};
    assert(countDistinct(numbers) == 6);
}