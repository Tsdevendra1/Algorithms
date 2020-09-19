//
// Created by Tharuka Devendra on 19/09/2020.
//

#include "TriangulatePolygon.h"
#include "vector"
#include "iostream"

using namespace std;


int getMinScoreToTriangulate(vector<int> &scoresForVertex) {
    int n = scoresForVertex.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int subArraySize = 3; subArraySize <= n; ++subArraySize) {
        for (int subArrayStart = 0; subArrayStart <= n - subArraySize; ++subArrayStart) {
            int subArrayEnd = (subArrayStart + subArraySize) - 1;
            dp[subArrayStart][subArrayEnd] = INT_MAX;
            for (int splittingPoint = subArrayStart + 1; splittingPoint < subArrayEnd; ++splittingPoint) {

                int product =
                        scoresForVertex[subArrayStart] *
                        scoresForVertex[splittingPoint] *
                        scoresForVertex[subArrayEnd];

                int current = dp[subArrayStart][splittingPoint] + dp[splittingPoint][subArrayEnd] + product;
                int previous = dp[subArrayStart][subArrayEnd];

                dp[subArrayStart][subArrayEnd] = min(current, previous);

            }
        }
    }
    return dp[0].back();
}

void testTriangulatePolygon() {
    vector<int> test = {3, 7, 4, 5};
    assert(getMinScoreToTriangulate(test) == 144);
}
