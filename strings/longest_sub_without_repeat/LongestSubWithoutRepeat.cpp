//
// Created by Tharuka Devendra on 28/07/2020.
//

#include <climits>
#include "LongestSubWithoutRepeat.h"
#include "string"
#include "iostream"
#include "unordered_set"
#include "unordered_map"

using namespace std;

string longestSubstringWithoutRepeatingNaive(string &original) {
    string answer;
    for (int startIndex = 0; startIndex < original.length(); ++startIndex) {
        unordered_set<char> seen;
        string currentSubString;
        for (int currentChar = startIndex; currentChar < original.length(); ++currentChar) {
            char current = original[currentChar];
            if (seen.find(current) != seen.end()) {
                break;
            }
            currentSubString += current;
            seen.insert(current);
        }

        if (currentSubString.size() > answer.size()) {
            answer = currentSubString;
        }
    }
    return answer;
}


int longestSubstringWithoutRepeatingOptimal(string &original){
    int left = 0;
    int right = 0;
    unordered_map<char, int> inCurrentWindow;
    int maxSize = INT_MIN;
    while(right < original.length()) {
        ++inCurrentWindow[original[right]];

        // should be less than because if there is a repeat then size of inCurrentWindow will be less that length of string e.g. ABB -> {A:1, B:2}.size() == 2 which is not equal to ABB.size() == 3
        while (left < right && inCurrentWindow.size() < (right-left+1)) {
            char currentChar = original[left];
            --inCurrentWindow[currentChar];
            if (inCurrentWindow[currentChar] == 0) {
                inCurrentWindow.erase(currentChar);
            }
            ++left;
        }

        maxSize = max(maxSize, (int) inCurrentWindow.size());
        ++right;
    }
    return maxSize;
}

void testLongestSubWithoutRepeating() {
    string test = "BBBB";
    string test2 = "ABABABAB";
    string test3 = "GEEKSFORGEEKS";
    assert(longestSubstringWithoutRepeatingNaive(test) == "B");
    assert(longestSubstringWithoutRepeatingNaive(test2) == "AB");
    assert(longestSubstringWithoutRepeatingNaive(test3) == "EKSFORG");

    assert(longestSubstringWithoutRepeatingOptimal(test) == 1);
    assert(longestSubstringWithoutRepeatingOptimal(test2) == 2);
    assert(longestSubstringWithoutRepeatingOptimal(test3) == 7);
}