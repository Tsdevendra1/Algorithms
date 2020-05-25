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
                i++;
            }
        }
    }
}

void KMPSearch(string pat, string txt) {
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

void testKMP() {
    string text = "GEEKS FOR GEEKS";
    string pattern = "GEEK";
    KMPSearch(pattern, text);
}
