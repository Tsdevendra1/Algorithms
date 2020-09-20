//
// Created by Tharuka Devendra on 20/09/2020.
//

#ifndef ALGORITHMS_RANGEQUERY_H
#define ALGORITHMS_RANGEQUERY_H
#include "vector"
using namespace std;

class RangeQuery {
    vector<int> sumUpToAndIncludingIndex;

public:
    explicit RangeQuery(vector<int> &array) {
        sumUpToAndIncludingIndex.resize(array.size());
        sumUpToAndIncludingIndex[0] = array[0];
        for (int i = 1; i < array.size(); ++i) {
            sumUpToAndIncludingIndex[i] = sumUpToAndIncludingIndex[i - 1] + array[i];
        }
    }

    int getRangeQuery(int queryStart, int queryEnd) {
        assert(queryEnd >= queryStart);
        int queryEndScore = queryStart == 0 ? 0 : sumUpToAndIncludingIndex[queryStart - 1];
        return sumUpToAndIncludingIndex[queryEnd] - queryEndScore;
    }
};


void testRangeQuery();


#endif //ALGORITHMS_RANGEQUERY_H
