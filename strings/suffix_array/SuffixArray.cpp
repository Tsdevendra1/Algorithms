//
// Created by Tharuka Devendra on 04/06/2020.
//

#include "SuffixArray.h"
#include <iostream>
#include <cstring>
#include <algorithm>
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

struct suffix {
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
};

// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
           (a.rank[0] < b.rank[0] ? 1 : 0);
}


vector<int> buildSuffixArray(string &txt) {
    vector<suffix> suffixes(txt.size());

    for (int i = 0; i < txt.size(); ++i) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = txt[i + 1] - 'a';
    }
    sort(suffixes.begin(), suffixes.end(), cmp);

    for (int k = 4; k < 2 * txt.size(); k *= 2) {
        int previousRank = suffixes[0].rank[0];
        int previousOtherRank = suffixes[0].rank[1];
        int rank = 1;
        suffixes[0].rank[0] = 1;
        vector<int> positions(suffixes.size());

        for (int i = 1; i < suffixes.size(); ++i) {

            if (suffixes[i].rank[0] != previousRank || suffixes[i].rank[1] != previousOtherRank) {
                ++rank;
            }

            previousRank = suffixes[i].rank[0];
            previousOtherRank = suffixes[i].rank[1];
            suffixes[i].rank[0] = rank;
            positions[suffixes[i].index] = i;
        }
        // set the other ranks properly now
        for (int i = 0; i < suffixes.size(); ++i) {
            int nextIndex = suffixes[i].index + (k / 2);
            suffixes[i].rank[1] = (nextIndex < suffixes.size()) ? suffixes[positions[nextIndex]].rank[0] : -1;
        }
        sort(suffixes.begin(), suffixes.end(), cmp);
    }

    vector<int> suffixArray(suffixes.size());
    for (int i = 0; i < suffixes.size(); ++i) {
        suffixArray[i] = suffixes[i].index;
    }
    return suffixArray;
}

void printArr(vector<int> &arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

void testSuffixArray() {
    string txtNew = "qlkjwalksjlsadkjwn";
    vector<int> answer = buildSuffixArray(txtNew);
    printArr(answer);
}