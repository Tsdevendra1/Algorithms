//
// Created by Tharuka Devendra on 10/06/2020.
//

#include "BitwiseOperations.h"
#include "string"
#include "iostream"

using namespace std;

string intToBinary(int number, int numberOfBits = 8) {
    string binary;
    while (number > 0) {
        char toAdd = (number % 2 == 0) ? '0' : '1';
        binary.insert(0, 1, toAdd);
        number = number >> 1;
    }
    int leftToFill = numberOfBits - binary.size();
    if (leftToFill > 0) {
        for (int i = 0; i < leftToFill; ++i) {
            binary.insert(0, 1, '0');
        }
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

int bitwiseAND(int number1, int number2) {
    string output;
    while (number1 > 0 || number2 > 0) {
        int bit1IsOne = number1 & 1;
        int bit2IsOne = number2 & 1;
        char charToInsert = (bit1IsOne && bit2IsOne) ? '1' : '0';
        output.insert(0, 1, charToInsert);
        number1 = number1 >> 1;
        number2 = number2 >> 1;
    }

    return binaryToInt(output);

}

string bitwiseNOT(string &number) {
    string output;
    for (char &binary: number) {
        output.push_back((binary == '1') ? '0' : '1');
    }
    return output;
}

int bitwiseXOR(int number1, int number2) {
    string output;
    while (number1 > 0 || number2 > 0) {
        int bit1IsOne = number1 & 1;
        int bit2IsOne = number2 & 1;
        char charToInsert = '0';
        if ((bit1IsOne == 1 && bit2IsOne == 0) || (bit1IsOne == 0 && bit2IsOne == 1))
            charToInsert = '1';
        output.insert(0, 1, charToInsert);
        number1 = number1 >> 1;
        number2 = number2 >> 1;
    }

    return binaryToInt(output);
}


string twosComplementBinaryRepresentation(int number) {
    // Twos complemwnt gets the negativ value of the number being operated on e.g -3 --> 3, 2 --> -2
    string twosComplement;
    string numberInBinary = intToBinary(number);
    string flippedBinary = bitwiseNOT(numberInBinary);
    int flippedNumber = binaryToInt(flippedBinary);
    flippedNumber += 1;
    return intToBinary(flippedNumber);
}


int getBit(int number, int index) {
    int mask = (1 << index);
    return (number & mask) != 0;
}

int setBit(int number, int index) {
    int mask = (1 << index);
    return number | mask;

}

int clearBit(int number, int index) {
    int mask = ~(1 << index);
    return number & mask;
}

int toggleBit(int number, int index) {
    int mask = (1 << index);
    return number ^ mask;
}

int updateBit(int number, int index, int value) {
    int numberWithCleared = clearBit(number, index);
    int orMask = (value == 1) ? 1 : 0;
    return numberWithCleared | (orMask << index);
}

int leastSignificantBitSet(int number) {
    return number & -number;
}

int highestPowerOf2DivisibleBy(int number) {
    return number & -number;
}

int negativeBinaryToInt(string number) {

    string positiveNumber = bitwiseNOT(number);
    int newNumber = binaryToInt(positiveNumber);
    return -(newNumber + 1);

}

void bitTricks() {
    // look at cracking the code interview - theyre pretty simple
}

void testBitwiseOperations() {
    string test = "110011111";
    string test2 = "110";
    assert(binaryToInt(test2) == 6);
    assert(bitwiseNOT(test) == "001100000");
    assert(updateBit(3, 1, 0) == 1);
    assert(toggleBit(3, 1) == 1);
    assert(clearBit(3, 0) == 2);
    assert(setBit(2, 0) == 3);
    assert(getBit(2, 1) == 1);
    assert(highestPowerOf2DivisibleBy(12) == 4);
    assert(negativeBinaryToInt("11110100") == -12);
    cout << bitwiseAND(40, 3) << endl;
    cout << bitwiseOR(93, 17) << endl;
    cout << bitwiseXOR(4, 3) << endl;
    cout << twosComplementBinaryRepresentation(2) << endl;
}