//
// Created by Tharuka Devendra on 16/06/2020.
//

#include <iostream>
#include "StonesGame.h"
#include "vector"
#include "numeric"

using namespace std;

class StonesGameSolution {
public:
    vector<int> stones;
    vector<vector<int>> dp;


    int memo(int start, int end, int isFirstPerson) {
        if (start > end){
            return 0;
        }


        int frontMove = memo(start+1, end, !isFirstPerson);
        int add = (isFirstPerson) ? stones[start] : 0;
        int frontMoveScore = frontMove + add;


        int backMove = memo(start, end-1, !isFirstPerson);
        int add2 = (isFirstPerson) ? stones[end] : 0;
        int backMoveScore = backMove + add2;

        if (isFirstPerson) {
            return max(frontMoveScore, backMoveScore);
        }
        return min(frontMoveScore, backMoveScore);

    }

    bool canWinStoneGame(vector<int> &stonesOriginal) {
        stones = stonesOriginal;
        dp.resize(stonesOriginal.size(), vector<int>(stonesOriginal.size(), -1));
        int totalSum = accumulate(stonesOriginal.begin(), stonesOriginal.end(), 0);
        int secondPlayerScore = memo(0, (int) stonesOriginal.size() - 1, false);
        cout << secondPlayerScore << endl;
        cout << totalSum - secondPlayerScore << endl;
        return secondPlayerScore < (totalSum - secondPlayerScore);


    }
};


void testStoneGame(){
    auto solution = make_unique<StonesGameSolution>();
    vector<int> stones = {5,3,4,5,3};
    cout << solution->canWinStoneGame(stones)<<endl;
}
