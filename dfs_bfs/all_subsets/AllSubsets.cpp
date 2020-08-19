//
// Created by Tharuka Devendra on 19/08/2020.
//

#include <iostream>
#include "AllSubsets.h"
#include "vector"
#include "numeric"
#include "queue"

using namespace std;

int numberOfSubsets(vector<int> &choices) {
    int n = choices.size();
    return pow(2, n);
}

vector<vector<int>> getAllSubsets(vector<int> &choices) {
    vector<vector<int>> answers = {{}};
    for (auto choice: choices) {
        int numberOfAnswers = answers.size();
        for (int currentAnswerIndex = 0; currentAnswerIndex < numberOfAnswers; ++currentAnswerIndex) {
            vector<int> currentAnswer = answers[currentAnswerIndex];
            currentAnswer.push_back(choice);
            answers.push_back(currentAnswer);
        }
    }
    return answers;
}

void testAllSubsets() {
    vector<int> test = {1, 2, 3};
    // This is all possible subsets for a size 3 vector (1 means that position was chosen, 0 means it wasn't chosen)
//    000
//    001
//    010
//    100
//    011
//    110
//    101
//    111
// do memo, stack with queue
    assert(numberOfSubsets(test) == 8);
    auto subsets = getAllSubsets(test);
    assert(subsets.size() == 8);
}
