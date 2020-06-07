//
//  main.cpp
//  Merge Sort
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <limits.h>

#define MAX_SIZE 10

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int L[MAX_SIZE] = {0};
    int R[MAX_SIZE] = {0};
    
    int i;
    for (i = 1; i <= n1; ++i)
        L[i] = A[p + i - 1];

    int j;
    for (j = 1; j <= n2; ++j)
        R[j] = A[q + j];
    
    L[i] = INT_MAX;
    R[j] = INT_MAX;
    
    i = 1;
    j = 1;
    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            ++i;
        } else {
            A[k] = R[j];
            ++j;
        }
    }
}

void sort(int A[], int p, int r) {
    if (p < r) {
        int q = p + ((r - p) / 2);
        sort(A, p, q);
        sort(A, q + 1, r);
        merge(A, p, q, r);
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
