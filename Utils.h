//
// Created by Tharuka Devendra on 05/06/2020.
//

#ifndef ALGORITHMS_UTILS_H
#define ALGORITHMS_UTILS_H

#include <iostream>
#include "vector"

using namespace std;


class Utils {
public:
    template<typename T>
    static void printArr(vector<T> arr) {
        for (auto i : arr)
            cout << i << " ";
        cout << endl;
    }

    template<typename T>
    static bool compareVectors(vector<T> &arr1, vector<T> &arr2) {
        if (arr1.size() != arr2.size()){
            return false;
        }
        for (auto a1: arr1) {
            bool found = false;
            for (auto a2: arr2) {
                if (a1 == a2) {
                    found = true;
                }
            }
            if (!found) {
                return false;
            }
        }
        return true;
    }
};


#endif //ALGORITHMS_UTILS_H
