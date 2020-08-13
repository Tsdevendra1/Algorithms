//
// Created by Tharuka Devendra on 08/08/2020.
//

#include "GeneratePermutations.h"
#include "iostream"
#include "vector"
#include "unordered_set"
#include "queue"

using namespace std;

class Permutations {
public:
    static vector<vector<int>> findPermutations(const vector<int> &nums) {

        vector<vector<int>> result;

        queue<vector<int>> permutations;

        permutations.push(vector<int>());

        for (auto currentNumber : nums) {
            // we will take all existing permutations and add the current number to create new
            // permutations
            int n = permutations.size();

            for (int i = 0; i < n; i++) {
                vector<int> oldPermutation = permutations.front();
                permutations.pop();
                // create a new permutation by adding the current number at every position
                for (int j = 0; j <= oldPermutation.size(); j++) {

                    vector<int> newPermutation(oldPermutation);
                    newPermutation.insert(newPermutation.begin() + j, currentNumber);

                    if (newPermutation.size() == nums.size()) {
                        result.push_back(newPermutation);
                    } else {
                        permutations.push(newPermutation);
                    }

                }
            }
        }

        return result;
    }
};


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
    auto perms = make_unique<Permutations>();
    auto answer2 = perms->findPermutations(choices);

    int similar = 0;
    for (auto &a1: answer) {
        for (auto &a2: answer2) {
            if (a1 == a2) {
                ++similar;
            }
        }
    }
    assert(similar == 6);
    assert(perms->findPermutations(choices).size() == 6);
    assert(answer.size() == 6);
}