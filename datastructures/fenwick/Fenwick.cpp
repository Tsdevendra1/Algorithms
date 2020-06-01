//
// Created by Tharuka Devendra on 01/06/2020.
//

#include "Fenwick.h"

void testFenwick(){
    auto fenwick = new Fenwick();
    vector<int> initialArray = {1,2,3,4,5,6};
    fenwick->construct(initialArray);
    assert(fenwick->prefixSum(0) == 1);
    assert(fenwick->prefixSum(1) == 3);
    assert(fenwick->prefixSum(2) == 6);
    assert(fenwick->prefixSum(3) == 10);
    assert(fenwick->prefixSum(4) == 15);
    assert(fenwick->prefixSum(5) == 21);
}
