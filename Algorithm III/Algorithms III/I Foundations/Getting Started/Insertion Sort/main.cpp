//
//  main.cpp
//  Insertion Sort
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_SIZE 10

void sort(int A[]) {
    for (int j = 2; j <= MAX_SIZE; ++j) {
        int key = A[j];
        int i = j - 1;
        while(i > 0 && A[i] > key) {
            A[i+1] = A[i];
            --i;
        }
        A[i+1] = key;
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
    int A[MAX_SIZE + 1] = {0, 10, 10, 9, 8, 7, 9, 3, 1, 2, 2};
    printArray(A);
    sort(A);
    printArray(A);
    return 0;
}
