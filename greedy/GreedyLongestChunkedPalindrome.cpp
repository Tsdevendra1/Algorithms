//
// Created by Tharuka Devendra on 08/09/2020.
//

#include "GreedyLongestChunkedPalindrome.h"
#include "string"
#include "iostream"

using namespace std;

//int longestDecompositionForLoop(string S) {
//    int res = 0;
//    int n = S.length();
//    string l;
//    string r;
//    for (int i = 0; i < n; ++i) {
//        l += S[i];
//        r = S[n - i - 1] + r;
//
//        if (l == r) {
//            ++res;
//            l.clear();
//            r.clear();
//        }
//
//    }
//    return res;
//}
//

int getLongestChunkedPalindromeForLoop(string &input) {
    int answer = 0;
    string leftString;
    string rightString;
    for (int leftIndex = 0; leftIndex < input.size(); ++leftIndex) {
        int rightIndex = (input.size() - 1) - leftIndex;
        leftString += input[leftIndex];
        rightString.insert(0, 1, input[rightIndex]);
        if (leftString == rightString) {
            ++answer;
            rightString.clear();
            leftString.clear();
        }
    }

    return answer;
}

int getLongestChunkedPalindrome(string &input) {
    string leftString;
    string rightString;
    int left = 0;
    int right = (int) input.length() - 1;
    int answer = 0;
    while (left <= right) {
        leftString += input[left];
        rightString.insert(0, 1, input[right]);
        if (leftString == rightString) {
            answer += (left == right) ? 1 : 2;
            leftString.clear();
            rightString.clear();
        }
        ++left;
        --right;
    }

    if (!leftString.empty()) {
        answer += 1;
    }

    return answer;
}

int getLongestChunkedPalindromeRecursion(string input, int answer = 0) {
    int stringLength = (int) input.length();
    for (int matchingStringLength = 1; matchingStringLength <= stringLength / 2; ++matchingStringLength) {
        int endIndex = stringLength - matchingStringLength;
        bool frontMatches = input[0] == input[endIndex];
        bool backMatches = input.back() == input[matchingStringLength - 1];
        if (!(backMatches && frontMatches)) {
            continue;
        }
        bool stringsMatch = input.substr(0, matchingStringLength) == input.substr(endIndex, matchingStringLength);
        if (stringsMatch) {
            int lengthRemoved = matchingStringLength * 2;
            int remainingLength = stringLength - lengthRemoved;
            string newString = input.substr(matchingStringLength, remainingLength);
            return getLongestChunkedPalindromeRecursion(newString, answer + 2);
        }
    }
    return (input.empty()) ? answer : answer + 1;
}

void testGreedyLongestChunkedPalindrome() {
    // if you want to understand the question just google leetcode longest chunked palindrome
    string test = "ghiabcdefhelloadamhelloabcdefghi";
    assert(getLongestChunkedPalindrome(test) == 7);
    assert(getLongestChunkedPalindromeForLoop(test) == 7);
    assert(getLongestChunkedPalindromeRecursion(test) == 7);
}
