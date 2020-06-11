//
// Created by Tharuka Devendra on 11/06/2020.
//

#include "PrimeNumbers.h"
#include "vector"
#include "numeric"
#include "map"
#include "../Utils.h"

using namespace std;

vector<int> findPrimeFactors(int number) {
    vector<int> factors;
    int divisor = 2;
    while (number > 1) {
        // we don't need to check if divisor is prime because if it wasn't we'd have already divided by its prime factor e.g 9 = 3 x 3
        while (number % divisor == 0) {
            factors.push_back(divisor);
            number /= divisor;
        }
        divisor += (divisor == 2) ? 1 : 2;
    }
    return factors;
}

bool isPrime(int number) {
    if (number < 2) {
        return false;
    }
    if (number % 2 == 0) {
        return false;
    }
    for (int i = 3; i < sqrt(number); ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}

map<int, int> orderPrimes(int number) {

    vector<int> primeFactors = findPrimeFactors(number);
    map<int, int> primes;
    for (int prime: primeFactors) {
        primes[prime] += 1;
    }
    return primes;
}

int lowestCommonMultiple(int number1, int number2) {
    map<int, int> primes1 = orderPrimes(number1);
    map<int, int> primes2 = orderPrimes(number2);

    int value = 1;
    for (auto &[prime, amount] : primes1) {
        int maxAmount = max(amount, primes2[prime]);
        value *= pow(prime, maxAmount);
    }
    for (auto &[prime, amount] : primes2) {
        if (primes1.find(prime) == primes1.end()) {
            value *= pow(prime, amount);
        }
    }
    return value;

}

int greaterCommonDivisor(int number1, int number2) {
    map<int, int> primes1 = orderPrimes(number1);
    map<int, int> primes2 = orderPrimes(number2);


    int value = 1;
    for (auto &[prime, amount] : primes1) {
        int maxAmount = min(amount, primes2[prime]);
        value *= pow(prime, maxAmount);
    }

    return value;
}

void primeNumberFacts() {
    // any number can be composed of multiplication of any prime number to the power - PRIME FACTORISATION;
    // e.g 84 = 2^2 * 3^1 * 5^0 * 7^1 * 11^0 ... (rest are to the power 0)
}

vector<int> generatePrimes(int upTo) {
    // Sieve of Eratosthenes algorithm
    vector<bool> isPrimeTracker(upTo + 1, true);
    isPrimeTracker[0] = false;
    isPrimeTracker[1] = false;
    int currentPrime = 2;
    while (currentPrime < sqrt(upTo)) {
        // can start at currentPrime squared because if we have a  k * prime, where k < prime, this value would have already been crossed off in a prior iteration
        for (int num = currentPrime * currentPrime; num < upTo + 1; num += currentPrime) {
            isPrimeTracker[num] = false;
        }

        currentPrime += 1;
        while (currentPrime < upTo + 1 && !isPrimeTracker[currentPrime]) {
            ++currentPrime;
        }
    }
    vector<int> primes;
    for (int i = 0; i < upTo + 1; ++i) {
        if (isPrimeTracker[i])
            primes.push_back(i);
    }
    return primes;
}


void testPrimeNumbers() {
    vector<int> factors = findPrimeFactors(97);
    assert(!isPrime(100));
    assert(isPrime(97));
    vector<int> primes = generatePrimes(15);
    Utils::printArr(factors);
    Utils::printArr(primes);
    assert(lowestCommonMultiple(4, 7) == 28);
    assert(greaterCommonDivisor(4, 7) == 1);
    assert(greaterCommonDivisor(48, 57) == 3);
    // see cracking the code interview for explanation of why this works
    assert((greaterCommonDivisor(48, 57) * lowestCommonMultiple(48, 57)) == (48 * 57));
};