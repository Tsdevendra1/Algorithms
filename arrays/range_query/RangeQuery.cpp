//
// Created by Tharuka Devendra on 20/09/2020.
//

#include "RangeQuery.h"
#include "vector"

using namespace std;


void testRangeQuery() {
    vector<int> array = {1, 2, 3, 4, 5};
    auto query = make_unique<RangeQuery>(array);
    assert(query->getRangeQuery(0, 1) == 3);
    assert(query->getRangeQuery(2, 3) == 7);
    assert(query->getRangeQuery(0, 4) == 15);
    assert(query->getRangeQuery(1, 3) == 9);
}