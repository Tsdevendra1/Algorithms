//
// Created by Tharuka Devendra on 18/05/2020.
//
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <string>

#include <numeric>
#include <sstream>
#include "prefix-sufix/KMP.h"


using namespace std;

#include "prefix-sufix/z_algorithm.h"
#include "prefix-sufix/LongestPalindromSub.h"

class Solution {
    vector<vector<int>> answer = {{}};
    vector<int> possibleNumbers;
    void dfs(vector<int> current, int currentIndex) {
        if (currentIndex >= possibleNumbers.size()) {
            return;
        }

        for (int i=currentIndex; i<possibleNumbers.size(); ++i) {
            current.push_back(possibleNumbers[i]);
            answer.push_back(current);
            dfs(current, i+1);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> currentR;
        possibleNumbers = nums;
        dfs(currentR, 0);
        return answer;
    }
};
int main() {
//    testZAlgorithm();
//    testLongest();
    testKMP();
    return 0;
}
