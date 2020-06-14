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
};


#endif //ALGORITHMS_UTILS_H
