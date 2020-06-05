//
// Created by Tharuka Devendra on 25/05/2020.
//
#include <string>
#include <iostream>
#include <numeric>

#include "z_algorithm.h"


using namespace std;
void getZarr(string str, int Z[]) {
    // str will already have dollar sign seperation
    int stringLength = str.size();

    int left = 0;
    int right = 0;
    int k = 0;

    for (int i=1; i< stringLength; ++i) {
        cout << left << " " << right << " " << i << endl;
        if (right < i) {
            left = right = i;
            while (right < stringLength && str[right-left] == str[right]) {
                ++right;
            }
            Z[i] = right-left;
            --right;
        } else {
            k = i-left;
            // If it is not out of bounds can use old value, because we know it stops within the bounds
            if (Z[k] < right-i+1) {
                Z[i] = Z[k];
            } else {
                // Need to calculate if going past the bounds can increase it
                left = i;
                while (right < stringLength && str[right-left] == str[right]) {
                    ++right;
                }
                Z[i] = right-left;
                --right;
            }
        }
    }
}

void zAlgorithm(string &pattern, string &text) {
// Create concatenated string "P$T"
    string concat = pattern + "$" + text;
    int l = concat.length();

    // Construct Z array
    int Z[l];
    getZarr(concat, Z);

    // now looping through Z array for matching condition
    for (int i = 0; i < l; ++i)
    {
        // if Z[i] (matched region) is equal to pattern
        // length we got the pattern
        if (Z[i] == pattern.length())
            cout << "Pattern found at index "
                 << i - pattern.length() -1 << endl;
    }
}

void testZAlgorithm(){
    string text = "GEEKS FOR GEEKS";
    string pattern = "GEEK";
    zAlgorithm(pattern, text);
}


