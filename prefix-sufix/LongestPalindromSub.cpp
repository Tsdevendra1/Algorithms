//
// Created by Tharuka Devendra on 25/05/2020.
//

#include "LongestPalindromSub.h"
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


int longestPalindromSub(string &str) {
    int stringLength = str.size();
    // row i, col j == 1 means that the sub string i-j (inclusive) is a palindrome
    vector<vector<int>> table(stringLength, vector<int>(stringLength));
    int paliStart;
    int maxPaliLength = 1;

    // This is for substrings of length 1;
    for (int i = 0; i < stringLength; ++i)
        table[i][i] = 1;

    // This is for substrings of length 2;
    for (int i = 0; i < stringLength - 1; ++i) {
        if (str[i] == str[i + 1]) {
            table[i][i + 1] = 1;
            paliStart = i;
            maxPaliLength = 2;
        }
    }

    // This is for substrings longer than 3;
    for (int subStringLength = 3; subStringLength < stringLength; ++subStringLength) {
        for (int i = 0; i < stringLength - subStringLength + 1; ++i) {
            int endIndex = i + subStringLength - 1;
            // table[i+1][endIndex-1] would be true if from i+1 to endIndex -1 is a palindrome
            if (table[i + 1][endIndex - 1] && str[i] == str[endIndex]) {
                table[i][endIndex] = 1;
                if (subStringLength > maxPaliLength) {
                    paliStart = i;
                    maxPaliLength = subStringLength;
                }
            }
        }
    }
    return maxPaliLength;
}

int longestPalindromBetter(string str) {
    int maxLength = 1; // The result (length of LPS)

    int start = 0;
    int stringLength = str.size();

    int low, high;

    // One by one consider every character as center point of
    // even and length palindromes
    for (int i = 1; i < stringLength; ++i) {
        // Find the longest even length palindrome
        // with center points as i-1 and i.
        low = i - 1;
        high = i;
        while (low >= 0 && high < stringLength && str[low] == str[high]) {
            if (high - low + 1 > maxLength) {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }

        // Find the longest odd length palindrome with center
        // point as i
        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < stringLength && str[low] == str[high]) {
            if (high - low + 1 > maxLength) {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }
    }

    cout << "Longest palindrome substring is: ";

    return maxLength;
}


void testLongest() {
    string testString = "wklqjewlkqjerttrekjlejwqlej";
    cout << longestPalindromSub(testString) << endl;
    cout << longestPalindromBetter(testString) << endl;
}
