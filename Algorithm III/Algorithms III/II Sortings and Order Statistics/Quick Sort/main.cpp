//
//  main.cpp
//  Quick Sort
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_SIZE 10

int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r-1; ++j) {
        if (A[j] <= x) {
            ++i;
            int tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
        }
    }
    A[r] = A[i + 1];
    A[i + 1] = x;
    
    return i + 1;
}

void sort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        sort(A, p, q - 1);
        sort(A, q + 1, r);
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
    printArray(A);
    sort(A, 1, 10);
    printArray(A);
    return 0;
}
