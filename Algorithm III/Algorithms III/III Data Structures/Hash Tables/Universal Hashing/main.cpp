//
//  main.cpp
//  Universal Hashing
//
//  Created by Alexis Quinto on 6/17/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

// for hashFunc()
const int r = 4;
int m1 = 701;
int A[r] = {
    rand() % m1,
    rand() % m1,
    rand() % m1,
    rand() % m1
};

// for hashFunc2()
int p = (pow(2, 51) - 1);
int b = (rand() % p);
int a = ((rand() % (p-1)) + 1);
int m2 = 10000;

// r is the size of vector based from the key
int hashFunc(int A[r], int K[r]) {
    // A[] = <a1, a2, a3, a4>
    // Values of Ai should range from 0 to m1 - 1
    // m1 is the size of the hash table which is a prime
    int h = 0;
    for (int i = 0; i < 4; ++i) {
        h += (A[i] * K[i]) % m1;
    }
    return h % m1;
}

// Use this hash function if the key universe U is an integer domain that can be fit into machine word
// U => [u] = {0,1,...,u-1} and [u] <= 2^w (where w = 64, the word length)
// For this example: we will assume that all given key k could have a maximum value of 2^50
long long hashFunc2(long long k) {
    // p is a prime number that could cover all possible keys which are in the range from 0 to p-1, inclusive
    // use Mersenne Prime Number => (2 ^ p) - 1
    // b should come from the set of {0,1,...,p-1}
    // a should come from the set of {1,2,...,p-1}
    // m2 is the size of hash table which can be arbitrary and not necessarily a prime (p > m2)

    long long h = (((a * k) + b) % p) % m2;
    
    return h;
}

// Radix notation where keys are viewed in base r (ex. r = 2^5 enough to represents 26 chars ~ a to z)
// Be careful not to exceed the maximum value of long long (2^64)
// For this example:
// all given str will be in lowercase (ie. "alexis")
// strLen is the length of the str
// rbits is the number of bits that could represent a subkey
long long radixNotation(char* str, int strLen, int rbits) {
    int index = strLen - 1;
    long long h = 0L;
    long long shift = 0L;
    while (index >= 0) {
        h += (str[index--] - 'a') << shift;
        shift += rbits;
    }
    return h;
}

int main(int argc, const char * argv[]) {
    // keys should viewed as vectors of subkeys
    // subkeys should be treated as base k (for this example: k = 255)
    int keys[r][r] {
        { 107, 105, 136, 147 }, // sample IP 1
        { 107, 105, 136, 148 }, // sample IP 2
        { 107, 105, 136, 149 }, // sample IP 3
        { 107, 105, 136, 147 } // sample IP 4
    };
    
    std::cout << "Hello, World!\n";
    std::cout << "Hash function 1: " << '\n';
    std::cout << "Hash value of IP 1: " << hashFunc(A, keys[0]) << '\n';
    std::cout << "Hash value of IP 2: " << hashFunc(A, keys[1]) << '\n';
    std::cout << "Hash value of IP 3: " << hashFunc(A, keys[2]) << '\n';
    std::cout << "Hash value of IP 4: " << hashFunc(A, keys[3]) << '\n';

    std::cout << "Hash function 2: " << '\n';
    long long k1 = radixNotation("alexis", 6, 5);
    long long k2 = radixNotation("alexir", 6, 5);
    std::cout << "Hash value of 'alexis': key["<< k1 << "] = " << hashFunc2(k1) << '\n';
    std::cout << "Hash value of 'alexir': key["<< k2 << "] = " << hashFunc2(k2) << '\n';
    std::cout << "Hash value of 'alexis': key["<< k1 << "] = " << hashFunc2(k1) << '\n';
    
    return 0;
}
