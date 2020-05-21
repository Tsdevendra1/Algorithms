//
// Created by Tharuka Devendra on 18/05/2020.
//
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

void createFenwick(vector<int> &tree, const vector<int> &array) {

    for (int i = 1; i < array.size() + 1; ++i) {
        tree[i] = array[i - 1];
    }

    for (int i = 1; i < array.size() + 1; ++i) {
        int lsb = i & -i;
        int j = i + lsb;
        if (j < array.size()+1) {
            tree[j] += tree[i];
        }
    }


}

int presum(vector<int> &tree, int index) {
    int sum = 0;
    int i = index + 1;
    while (i != 0) {
        sum += tree[i];
        i -= (i & -i);
    }

    return sum;

}

int presumRange(vector<int> &tree, int index1, int index2){
    return presum(tree, index1) - presum(tree, index2-1);
}

bool randomi(vector<int> &arr){
    short m[2001] = {}, s[1001] = {};
    for (auto n : arr)
        ++m[n + 1000];
    for (auto i = 0; i < 2001; ++i)
        if (m[i] && ++s[m[i]] > 1) return false;
    return true;
}

int main() {
    vector<int> arr = {0, 1,2,2,3,3, 4,5};
    randomi(arr);

}