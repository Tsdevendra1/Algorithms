//
// Created by Tharuka Devendra on 19/08/2020.
//

#include <iostream>
#include "AllSubsets.h"
#include "vector"
#include "numeric"
#include "queue"
#include "../../Utils.h"

using namespace std;

int numberOfSubsets(vector<int> &choices) {
    int n = choices.size();
    return pow(2, n);
}

void backtrack(vector<int> &current, int currentPosition, vector<int> &choices, vector<vector<int>> &answers) {
    if (currentPosition >= choices.size()) {
        answers.push_back(current);
        return;
    }

    // excluding current element
    backtrack(current, currentPosition + 1, choices, answers);
    int valueForPosition = choices[currentPosition];

    // adding current element
    current.push_back(valueForPosition);
    backtrack(current, currentPosition + 1, choices, answers);
    current.pop_back();

}

vector<vector<int>> getAllSubsetsBacktrack(vector<int> &choices) {
    vector<vector<int>> answer;
    vector<int> random = {};
    backtrack(random, 0, choices, answer);
    return answer;
}


void backtrack2(vector<int> &currentSet, int currentPosition, vector<int> &choices, vector<vector<int>> &answer) {
    // this method builds up by size (first iteration is size 1, then size 2, etc....
    // by for looping we can include and skip each position for the corresponding subsequent sizes
    answer.push_back(currentSet);

    for (int position = currentPosition; position < choices.size(); ++position) {
        int value = choices[position];
        currentSet.push_back(value);
        backtrack2(currentSet, position + 1, choices, answer);
        currentSet.pop_back();
    }
}

vector<vector<int>> getAllSubsetsBacktrack2(vector<int> &choices) {
    vector<vector<int>> answer = {};
    vector<int> random = {};
    backtrack2(random, 0, choices, answer);
    return answer;
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
    auto subsetsBacktrack = getAllSubsetsBacktrack(test);
    auto subsetsBacktrack2 = getAllSubsetsBacktrack2(test);

    assert(subsets.size() == 8);
    assert(subsetsBacktrack.size() == 8);
    assert(subsetsBacktrack2.size() == 8);
    assert(Utils::compareVectors(subsets, subsetsBacktrack));
    assert(Utils::compareVectors(subsetsBacktrack2, subsetsBacktrack));

}
