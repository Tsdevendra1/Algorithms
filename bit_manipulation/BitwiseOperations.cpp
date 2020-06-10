//
// Created by Tharuka Devendra on 10/06/2020.
//

#include "BitwiseOperations.h"
#include "string"
#include "iostream"

using namespace std;

string intToBinary(int number) {
    string binary;
    while (number > 0) {
        binary += (number % 2 == 0) ? '0' : '1';
        number = number >> 1;
    }
    return binary;
}


int binaryToInt(string &number) {
    string currentString = number;
    unsigned int currentMultiplier = 1;
    int currentNumber = 0;
    while (!currentString.empty()) {
        if (currentString.back() == '1') {
            currentNumber += (int) currentMultiplier;
        }
        currentMultiplier = currentMultiplier << (unsigned) 1;
        currentString.pop_back();
    }
    return currentNumber;
}

int bitwiseOR(int number1, int number2) {

    string output;
    while (number1 > 0 || number2 > 0) {
        int bit1IsOne = number1 & 1;
        int bit2IsOne = number2 & 1;
        char charToInsert = (bit1IsOne || bit2IsOne) ? '1' : '0';
        output.insert(0, 1, charToInsert);
        number1 = number1 >> 1;
        number2 = number2 >> 1;
    }

    return binaryToInt(output);

}

int bitwiseAND(string &number) {}

string bitwiseNOT(string &number) {
    string output;
    for (char &binary: number) {
        output.push_back((binary == '1') ? '0' : '1');
    }
    return output;
}

int bitwiseOXOR(string &number) {}

string twosComplementBinaryRepresentation(int number) {
    // Twos complemwnt gets the negativ value of the number being operated on e.g -3 --> 3, 2 --> -2
    string twosComplement;
    string numberInBinary = intToBinary(number);
    string flippedBinary = bitwiseNOT(numberInBinary);
    int flippedNumber = binaryToInt(flippedBinary);
    flippedNumber += 1;

    return intToBinary(flippedNumber);
}


int getBit() {}

int setBit() {}

int clearBit() {}

int updateBit() {}

void testBitwiseOperations() {
    string test = "110011111";
    string test2 = "110";
    cout << binaryToInt(test) << endl;
    cout << bitwiseNOT(test2) << endl;
//    cout << twosComplementBinaryRepresentation(1) << endl;
}