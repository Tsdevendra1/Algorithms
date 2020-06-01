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
#include "strings/KMP.h"
#include "strings/z_algorithm.h"
#include "strings/LongestPalindromSub.h"
#include "strings/DeBruijn.h"
#include "graphs/Hierholzer.h"


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
string r(){
    string s;
    if (s.empty()){
        return "";
    }
    string currentString;
    string finalString;
    for (int i=s.size()-1; i>=0; --i) {
        char current = s[i];
        if (current == ' '){
            currentString += ' ' + finalString;
            finalString = currentString;
            currentString = "";
        } else {
            currentString.push_back(current);
        }
    }
    finalString = currentString + ' ' + finalString;

    finalString.pop_back();
    return finalString;
}
int main() {
//    testZAlgorithm();
//    testLongest();
//    testKMP();
    testDeBruijn();
//    testHierholzer();
    for (int i=3; 0 < i; --i){
        cout << i << endl;
    }
    return 0;
}
