//
// Created by Tharuka Devendra on 08/08/2020.
//

#include "GeneratePermutations.h"
#include "iostream"
#include "vector"
#include "unordered_set"
#include "queue"

using namespace std;

vector<vector<int>> generateAllPermutations(vector<int> &choices) {
    vector<int> possibleChoices = choices;
    queue<pair<unordered_set<int>, vector<int>>> tracker;
    tracker.push({});
    vector<vector<int>> answer;
    while (!tracker.empty()) {
        auto seen = tracker.front().first;
        auto currentMove = tracker.front().second;
        tracker.pop();

        if (currentMove.size() == possibleChoices.size()) {
            answer.push_back(currentMove);
            continue;
        }

        for (int choice: possibleChoices) {
            if (seen.find(choice) == seen.end()) {
                currentMove.push_back(choice);
                seen.insert(choice);

                tracker.push({seen, currentMove});

                currentMove.pop_back();
                seen.erase(choice);
            }
        }
    }
    return answer;
}

void testGeneratePermutations() {
    vector<int> choices = {1, 2, 3};
    auto answer = generateAllPermutations(choices);
    assert(answer.size() == 6);
}