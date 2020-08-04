//
// Created by Tharuka Devendra on 14/06/2020.
//

#include "Permutations.h"
#include "vector"
#include "../../Utils.h"

using namespace std;

class Wrapper {
public:
    int arrSize;
    vector<char> &choices;
    vector<string> perms;

    explicit Wrapper(int arrSize, vector<char> &choices) : arrSize(arrSize), choices(choices) {};

    void createPerms(const string &current, int index) {
        perms.push_back(current);

        if (index >= arrSize) {
            return;
        }
        for (int i = index; i < arrSize; i++) {
            createPerms(current + choices[i], i + 1);
        }
    }
};

vector<string> getPerms(vector<char> &choices) {
    auto wrapper = make_unique<Wrapper>(choices.size(), choices);
    wrapper->createPerms("", 0);
    return wrapper->perms;
}

vector<string> getPermsForLoop(vector<char> &choices) {
    vector<string> perms = {""};
    for (auto choice:choices) {
        int size = perms.size();
        for (int i=0; i<size; ++i) {
            perms.push_back(choice + perms[i]);
        }
    }
    return perms;
}

void testPermutations() {
    vector<char> possibilities = {'a', 'b', 'c'};
    vector<string> perms = getPerms(possibilities);
    vector<string> perms1 = getPermsForLoop(possibilities);
    Utils::printArr(perms);
    Utils::printArr(perms1);
}
