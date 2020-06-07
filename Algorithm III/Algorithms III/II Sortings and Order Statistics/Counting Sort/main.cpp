//
//  main.cpp
//  Counting Sort
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_SIZE 10
#define K 10

void sort(int A[], int B[]) {
    int C[K + 1] = {0};
    for (int j = 1; j <= MAX_SIZE; ++j)
        C[A[j]] += 1;
    for (int i = 1; i <= K; ++i)
        C[i] += C[i-1];
    for (int j = MAX_SIZE; j >= 1; --j) {
        B[C[A[j]]] = A[j];
        C[A[j]] -= 1;
    }
}

void printArray(int A[]) {
    for (int i = 1; i <= MAX_SIZE; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    int A[MAX_SIZE + 1] = {0, 10, 9, 8, 6, 7, 9, 3, 1, 2, 5};
    int B[MAX_SIZE + 1] = {0};
    printArray(A);
    sort(A, B);
    printArray(B);
    return 0;
}
