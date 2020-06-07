//
// Created by Tharuka Devendra on 04/06/2020.
//

#include "SuffixArray.h"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct suffix {
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
};

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


vector<int> kasai(string &txt, vector<int> &suffixArr) {

    int n = suffixArr.size();
    int suffixArrSize = suffixArr.size();

    // To store LCP array
    vector<int> lcp(n, 0);

    vector<int> invSuff(n);

    for (int i = 0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++) {
        int positionInSuffixArray = invSuff[i];
        int positionInTextFirst = i;
        if (positionInSuffixArray == suffixArrSize - 1) {
            k = 0;
            continue;
        }

        int positionInTextSecond = suffixArr[positionInSuffixArray + 1];

        while (positionInTextFirst + k < suffixArrSize && positionInTextSecond + k < suffixArrSize &&
               txt[positionInTextFirst + k] == txt[positionInTextSecond + k]) {
            ++k;
        }

        lcp[positionInSuffixArray] = k;

        if (k > 0)
            k--;
    }

    return lcp;
}

int getLongestRepeatedSubstring(string &txt) {
    vector<int> suffixArray = buildSuffixArray(txt);
    vector<int> lcpArray = kasai(txt, suffixArray);
    // note that there could be multiple maxes so you should return them all
    int maxLcpValue = *max_element(lcpArray.begin(), lcpArray.end());
    return maxLcpValue;
}

void printArr(vector<int> &arr) {
    for (int i : arr)
        cout << i << " ";
    cout << endl;
}

void testSuffixArray() {
    string txtNew = "banana";
    vector<int> answer = buildSuffixArray(txtNew);

    vector<int> lcpArray = kasai(txtNew, answer);
    vector<int> expectedLcpArray = {1, 3, 0, 0, 2, 0};
    assert(expectedLcpArray == lcpArray);
    printArr(lcpArray);

    string repeatedString = "ABRACADABRA"; // answer should be 4 because ABRA is repeated twice
    int longestRepeatedSubstringLength = getLongestRepeatedSubstring(repeatedString);
    assert(longestRepeatedSubstringLength == 4);
}