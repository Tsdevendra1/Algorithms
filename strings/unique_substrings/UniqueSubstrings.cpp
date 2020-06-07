//
// Created by Tharuka Devendra on 07/06/2020.
//

#include "UniqueSubstrings.h"
#include "vector"
#include "string"
#include "../../Utils.h"

using namespace std;

struct suffix {
    int index;
    int rank[2];
};

vector<int> getSuffixArray(string &txt) {
    vector<suffix> suffixes;

    for (int i = 0; i < txt.size(); ++i) {
        int rankOne = txt[i] - 'a';
        int rankTwo = (i < txt.size() - 1) ? txt[i + 1] - 'a' : -1;
        auto newSuffix = suffix{i, {rankOne, rankTwo}};
        suffixes.push_back(newSuffix);
    }

    auto compareFunction = [](suffix one, suffix two) {
        if (one.rank[0] == two.rank[0]) {
            return one.rank[1] < two.rank[1];
        }
        return one.rank[0] < two.rank[0];
    };

    sort(suffixes.begin(), suffixes.end(), compareFunction);

    for (int k = 4; k < 2 * txt.size(); k *= 2) {
        int previousRankFirst = suffixes[0].rank[0];
        int previousRankSecond = suffixes[0].rank[1];
        suffixes[0].rank[0] = 1;
        int rank = 1;
        vector<int> positions(suffixes.size());

        for (int i = 1; i < suffixes.size(); ++i) {
            if (suffixes[i].rank[0] != previousRankFirst || suffixes[i].rank[1] != previousRankSecond) {
                ++rank;
            }
            previousRankFirst = suffixes[i].rank[0];
            previousRankSecond = suffixes[i].rank[1];
            suffixes[i].rank[0] = rank;
            positions[suffixes[i].index] = i;
        }
        for (int i = 0; i < suffixes.size(); ++i) {
            int nextIndex = suffixes[i].index + (k / 2);
            suffixes[i].rank[1] = (nextIndex < suffixes.size()) ? suffixes[positions[nextIndex]].rank[0] : -1;
        }

        sort(suffixes.begin(), suffixes.end(), compareFunction);

    }

    vector<int> suffixArray(suffixes.size());
    for (int i = 0; i < suffixes.size(); ++i) {
        suffixArray[i] = suffixes[i].index;
    }
    return suffixArray;
}

//vector<int> getLcpArray() {
//    vector<int> lcpArray;
//    return lcpArray;
//}

//int getNumberOfUniqueSubstrings() {
//
//}

void testUniqueSubstrings() {
    string text = "banana";
    vector<int> suffixArray = getSuffixArray(text);
    Utils::printArr(suffixArray);

}
