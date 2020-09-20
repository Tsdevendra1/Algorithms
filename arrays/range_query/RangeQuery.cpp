//
// Created by Tharuka Devendra on 20/09/2020.
//

#include "RangeQuery.h"
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

    int getRangeQuery(int queryStart, int queryEnd, vector<int> &array) {
        assert(queryEnd >= queryStart);
        int queryEndScore = queryStart == 0 ? 0 : sumUpToAndIncludingIndex[queryStart - 1];
        return sumUpToAndIncludingIndex[queryEnd] - queryEndScore;
    }
};


void testRangeQuery() {
    vector<int> array = {1, 2, 3, 4, 5};
    auto query = make_unique<RangeQuery>(array);
    assert(query->getRangeQuery(0, 1, array) == 3);
    assert(query->getRangeQuery(2, 3, array) == 7);
    assert(query->getRangeQuery(0, 4, array) == 15);
    assert(query->getRangeQuery(1, 3, array) == 9);
}