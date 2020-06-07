//
// Created by Tharuka Devendra on 07/06/2020.
//

#include <numeric>
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

vector<int> getLcpArray(string &txt, vector<int> &suffixArr) {
    vector<int> inverseSuffix(suffixArr.size());
    vector<int> lcpArray(suffixArr.size());

    for (int i = 0; i < suffixArr.size(); ++i) {
        inverseSuffix[suffixArr[i]] = i;
    }

    int lcpValue = 0;
    int txtSize = txt.size();
    for (int positionStart = 0; positionStart < txt.size(); ++positionStart) {
        int positionInSuffix = inverseSuffix[positionStart];
        if (positionInSuffix == txtSize - 1) {
            lcpValue = 0;
            continue;
        }
        int otherPositionInText = suffixArr[positionInSuffix + 1];
        while (otherPositionInText + lcpValue < txtSize && positionStart + lcpValue < txtSize &&
               txt[positionStart + lcpValue] == txt[otherPositionInText + lcpValue]) {
            ++lcpValue;
        }

        lcpArray[positionInSuffix] = lcpValue;
        if (lcpValue > 0) {
            --lcpValue;
        }
    }

    return lcpArray;
}

int getNumberOfUniqueSubstrings(string &txt) {
    vector<int> suffixArray = getSuffixArray(txt);
    vector<int> lcp = getLcpArray(txt, suffixArray);
    int n = txt.size();
    int numberOfSubstrings = (n*(n+1))/2;
    return numberOfSubstrings - accumulate(lcp.begin(), lcp.end(), 0);
}

void testUniqueSubstrings() {
    string text = "azaza";
    vector<int> suffixArray = getSuffixArray(text);
    vector<int> lcp = getLcpArray(text, suffixArray);

    Utils::printArr(lcp);

    cout << getNumberOfUniqueSubstrings(text) << endl;
    assert (getNumberOfUniqueSubstrings(text) == 9);
}
