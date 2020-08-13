//
// Created by Tharuka Devendra on 13/08/2020.
//

#include "IncreasingDecreasingSequence.h"
#include "string"
#include "vector"
#include "iostream"
#include "unordered_set"

using namespace std;

void
dfsBruteForce(vector<int> &current, unordered_set<int> &used, vector<int> &choices, int &answer, string &sequence) {
    if (current.size() == choices.size()) {
        bool passed = true;
        for (int i = 0; i < sequence.size(); ++i) {
            if (sequence[i] == 'D' && current[i] <= current[i + 1]) {
                passed = false;
            } else if (sequence[i] == 'I' && current[i] >= current[i + 1]) {
                passed = false;
            }
        }
        if (passed) {
            ++answer;
        }
        return;
    }

    for (int choice: choices) {
        if (used.find(choice) != used.end()) {
            continue;
        }
        current.push_back(choice);
        used.insert(choice);
        dfsBruteForce(current, used, choices, answer, sequence);
        current.pop_back();
        used.erase(choice);
    }
}


int getNumberOfIncreasingDecreasingSequenceBruteForce(string &sequence) {
    vector<int> choices;
    for (int i = 0; i <= sequence.size(); ++i) {
        choices.push_back(i);
    }
    int answer = 0;
    vector<int> current = {};
    unordered_set<int> used;
    dfsBruteForce(current, used, choices, answer, sequence);
    return answer;
}

int
dfs(int previouslyFilledIndex, int lower, int higher, const string &sequence, vector<vector<int>> &dp, int MOD) {
    if (previouslyFilledIndex == sequence.size()) {
        return 1;
    }

    char previousLetter = sequence[previouslyFilledIndex];
    int count = 0;
    if (dp[lower][higher] != -1) {
        return dp[lower][higher];
    }
    if (previousLetter == 'D') {
        if (lower > 0) {
            for (int positionChosen = 0; positionChosen < lower; ++positionChosen) {
                count += dfs(previouslyFilledIndex + 1, lower - positionChosen - 1, higher + positionChosen, sequence,
                             dp, MOD);
                count = count % MOD;
            }
        }
    } else {
        if (higher > 0) {
            for (int positionChosen = 0; positionChosen < higher; ++positionChosen) {
                count += dfs(previouslyFilledIndex + 1, lower + positionChosen, higher - positionChosen - 1, sequence,
                             dp, MOD);
                count = count % MOD;
            }
        }
    }
    dp[lower][higher] = count;
    return count;


}

int getNumberOfIncreasingDecreasingSequence(string &sequence) {
    int answer = 0;
    vector<vector<int>> dp(sequence.size()+1, vector<int>(sequence.size()+1, -1));
    int MOD = 1000000007;
    for (int number = 0; number <= sequence.size(); ++number) {
        answer += dfs(0, number, (int) sequence.size() - number, sequence, dp, MOD);
        answer = answer % MOD;
    }
    return answer;
}

void testIncreasingDecreasingSequence() {
    string test = "DIDDII";
    int answer = getNumberOfIncreasingDecreasingSequenceBruteForce(test);
    assert(answer == 111);
    string test2 = "DIDDII";
    int answer2 = getNumberOfIncreasingDecreasingSequence(test2);
    assert(answer2 == 111);
}
