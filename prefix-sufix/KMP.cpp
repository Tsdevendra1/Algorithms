//
// Created by Tharuka Devendra on 25/05/2020.
//
//
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

#include "KMP.h"

void computeLPSArray(string &pattern, int patternLength, int lps[]) {
    int lengthLongestPrefixSuffix = 0;

    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < patternLength) {
        if (pattern[i] == pattern[lengthLongestPrefixSuffix]) {
            ++lengthLongestPrefixSuffix;
            lps[i] = lengthLongestPrefixSuffix;
            ++i;
        } else {
            if (lengthLongestPrefixSuffix != 0) {
                lengthLongestPrefixSuffix = lps[lengthLongestPrefixSuffix - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }
}

void KMPSearch(string pat, string txt) {
    int patternLength = pat.size();
    int textLength = txt.size();

    int lps[patternLength];

    computeLPSArray(pat, patternLength, lps);

    int txtIndex = 0;
    int patternIndex = 0;
    while (txtIndex < textLength) {
        if (pat[patternIndex] == txt[txtIndex]) {
            ++txtIndex;
            ++patternIndex;
        }
        if (patternIndex == patternLength) {
            printf("Found pattern at index %d ", txtIndex - patternIndex);
            patternIndex = lps[patternIndex - 1];
        } else if (txtIndex < textLength && pat[patternIndex] != txt[txtIndex]) {
            if (patternIndex != 0) {
                patternIndex = lps[patternIndex - 1];
            } else {
                ++txtIndex;
            }
        }
    }
}

void testKMP() {
    string text = "GEEKS FOR GEEKS";
    string pattern = "GEEKS";
    KMPSearch(pattern, text);
}
