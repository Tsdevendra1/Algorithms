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

using namespace std;

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
    char x = 'a';
    bool r = 'a' < 9999;
    min(3, 3)
    cout << r << endl;
return 0;
}
