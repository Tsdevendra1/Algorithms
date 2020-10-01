//
// Created by Tharuka Devendra on 01/10/2020.
//

#include "NumSubPalindrom.h"
#include "string"

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

void testNumSubPalindrom() {
    string test = "aaab";
    assert(numberOfSubPalindromesBruteForce(test) == 7);
}
