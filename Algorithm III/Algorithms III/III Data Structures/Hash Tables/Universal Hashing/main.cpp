//
//  main.cpp
//  Universal Hashing
//
//  Created by Alexis Quinto on 6/17/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

#define R 4 // length of vector based from the key
#define M 701 // m is prime which is the size of hash table

using namespace std;

int hashFunc(int a[R], int k[R]) {
    int h = 0;
    for (int i = 0; i < 4; ++i) {
        h += (a[i] * k[i]) % M;
    }
    return h % M;
}

int main(int argc, const char * argv[]) {
    int a[R] = {
        rand() % M,
        rand() % M,
        rand() % M,
        rand() % M
    };
    
    // keys are
    int keys[R][R] {
        { 107, 105, 136, 147 }, // sample IP 1
        { 107, 105, 136, 148 }, // sample IP 2
        { 107, 105, 136, 149 }, // sample IP 3
        { 107, 105, 136, 147 } // sample IP 4
    };
    
    int h1 = hashFunc(a, keys[0]);
    int h2 = hashFunc(a, keys[1]);
    int h3 = hashFunc(a, keys[2]);
    int h4 = hashFunc(a, keys[3]);
    
    std::cout << "Hello, World!\n";
    std::cout << "Hash value of IP 1: " << h1 << '\n';
    std::cout << "Hash value of IP 2: " << h2 << '\n';
    std::cout << "Hash value of IP 3: " << h3 << '\n';
    std::cout << "Hash value of IP 4: " << h4 << '\n';
    
    return 0;
}
