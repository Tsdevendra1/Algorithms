//
// Created by Tharuka Devendra on 08/08/2020.
//

#include "GeneratePermutations.h"
#include "iostream"
#include "vector"
#include "unordered_set"
#include "queue"
#include "../../Utils.h"

using namespace std;

vector<vector<int>> perms1(const vector<int> &nums) {

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


vector<vector<int>> perms2(vector<int> &choices) {
    // Theres also the DFS version of this
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


void perms3Helper(vector<int> &choices, int swapPosition, vector<vector<int>> &answer) {
    // Base case
    if (swapPosition == choices.size() - 1) {
        answer.push_back(choices);
    } else {
        // Permutations made
        for (int i = swapPosition; i < choices.size(); i++) {
            swap(choices[swapPosition], choices[i]);
            perms3Helper(choices, swapPosition + 1, answer);
            swap(choices[swapPosition], choices[i]);
        }
    }
}

vector<vector<int>> perms3(vector<int> &choices) {
    vector<vector<int>> answer;
    perms3Helper(choices, 0, answer);
    return answer;
}

bool perms3UniquePermutationShouldSwap(vector<int> &choices, int swapPosition, int toSwapWithPosition) {
    for (int i = swapPosition; i < toSwapWithPosition; ++i) {
        if (choices[toSwapWithPosition] == choices[i]) {
            return false;
        }
    }
    return true;
}

void perms3HelperUniquePermutations(int swapPosition, vector<int> &choices, vector<vector<int>> &answer) {
    if (swapPosition == choices.size() - 1) {
        answer.push_back(choices);
    } else {
        for (int toSwapWith = swapPosition; toSwapWith < choices.size(); ++toSwapWith) {
            bool shouldSwap = perms3UniquePermutationShouldSwap(choices, swapPosition, toSwapWith);
            if (shouldSwap) {
                swap(choices[swapPosition], choices[toSwapWith]);
                perms3HelperUniquePermutations(swapPosition + 1, choices, answer);
                swap(choices[swapPosition], choices[toSwapWith]);
            }
        }
    }
}

vector<vector<int>> perms3UniquePermutations(vector<int> &choices) {
    vector<vector<int>> answer;
    perms3HelperUniquePermutations(0, choices, answer);
    return answer;
}


void testGeneratePermutations() {
    vector<int> choices = {1, 2, 3};
    auto answer = perms2(choices);
    auto answer2 = perms1(choices);
    auto answer3 = perms3(choices);

    vector<int> choicesWithDuplicates = {1, 2, 3, 1};
    auto answer4 = perms3UniquePermutations(choicesWithDuplicates);
    assert(answer4.size() == 12);

    int similar = 0;
    for (auto &a1: answer) {
        for (auto &a2: answer2) {
            if (a1 == a2) {
                ++similar;
            }
        }
    }
    assert(similar == 6);
    assert(perms1(choices).size() == 6);
    assert(answer.size() == 6);
    assert(answer3.size() == 6);
}