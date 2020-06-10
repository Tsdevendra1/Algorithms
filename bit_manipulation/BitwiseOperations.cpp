//
// Created by Tharuka Devendra on 10/06/2020.
//

#include "BitwiseOperations.h"
#include "string"
#include "iostream"

using namespace std;

int binaryToInt(string &number){
    string currentString = number;
    int currentMultiplier = 1;
    int currentNumber = 0;
    while (!currentString.empty()) {
        if (currentString.back() == '1') {
            currentNumber += currentMultiplier;
        }
        currentMultiplier = currentMultiplier << 1;
        currentString.pop_back();
    }
    return currentNumber;
}

int bitwiseOR(int number1, int number2) {

    string output;
    while (number1 > 0 && number2 > 0) {
        int bit1IsOne = number1 & 1;
        int bit2IsOne = number2 & 1;
        char charToInsert = (bit1IsOne || bit2IsOne) ? '1' : '0';
        output.insert(0, 1, charToInsert);
        number1 = number1 >> 1;
        number2 = number2 >> 1;
    }

}

int bitwiseAND(string &number) {}

int bitwiseNOT(string &number) {}

int bitwiseOXOR(string &number) {}


int getBit() {}

int setBit() {}

int clearBit() {}

int updateBit() {}

void testBitwiseOperations() {
    string test = "110011111";
    cout << binaryToInt(test) << endl;
}