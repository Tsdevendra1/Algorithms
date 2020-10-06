//
// Created by Tharuka Devendra on 01/10/2020.
//

#include <numeric>
#include "NumSubPalindrom.h"
#include "string"
#include "vector"
#include "iostream"

using namespace std;

int checkPalindromeLength(int startingAt, string &stringToCheck) {
    int n = stringToCheck.length();
    if (startingAt < 0 || startingAt > n) {
        return -1;
    }

    int left = startingAt;
    int right = startingAt;
    int counter = 0;
    while (left >= 0 && right < n && stringToCheck[left] == stringToCheck[right]) {
        ++counter;
        --left;
        ++right;
    }

    int counter2 = 0;
    left = startingAt;
    right = startingAt + 1;
    while (left >= 0 && right < n && stringToCheck[left] == stringToCheck[right]) {
        ++counter2;
        --left;
        ++right;
    }

    return counter + counter2;
}

int numberOfSubPalindromesBruteForce(string &stringToTest) {
    int n = stringToTest.length();
    int answer = 0;
    for (int palindromeStart = 0; palindromeStart < n; ++palindromeStart) {
        answer += checkPalindromeLength(palindromeStart, stringToTest);
    }
    return answer;
}

int numberOfSubPalindromesBottomUp(string &stringToTest) {
    int n = stringToTest.length();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int subStringStart = n - 1; subStringStart >= 0; --subStringStart) {
        for (int subStringEnd = subStringStart; subStringEnd < n; ++subStringEnd) {
            int space = subStringEnd - subStringStart;
            char letterOne = stringToTest[subStringEnd];
            char letterTwo = stringToTest[subStringStart];
            bool isPalindrome = false;
            if (space == 0) {
                isPalindrome = true;
            } else if (letterOne == letterTwo) {
                if (space == 1 || dp[subStringStart + 1][subStringEnd - 1] == 1) {
                    isPalindrome = true;
                }
            }

            if (isPalindrome) {
                dp[subStringStart][subStringEnd] = 1;
            }
        }
    }

    int count = 0;
    for (auto &array: dp) {
        count += accumulate(array.begin(), array.end(), 0);
    }
    return count;
}

void testNumSubPalindrom() {
    string test = "aaa";
    assert(numberOfSubPalindromesBottomUp(test) == 6);
    assert(numberOfSubPalindromesBruteForce(test) == 6);
}
