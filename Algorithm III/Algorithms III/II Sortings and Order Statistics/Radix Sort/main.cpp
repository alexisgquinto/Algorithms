//
//  main.cpp
//  Radix Sort
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_SIZE 7
#define WORD_SIZE 3
#define K 9

void copyStr(char src[], char des[]) {
    while(*src != '\0')
        *des++ = *src++;
    *des = '\0';
}

void countingSort(char A[][WORD_SIZE + 1], char B[][WORD_SIZE + 1], int d) {
    int C[K + 1] = {0};
    for (int j = 1; j <= MAX_SIZE; ++j){
        int c = A[j][d] - '0';
        C[c] += 1;
    }
    for (int i = 1; i <= K; ++i)
        C[i] += C[i - 1];
    for (int j = MAX_SIZE; j>= 1; --j) {
        int c = A[j][d] - '0';
        copyStr(A[j], B[C[c]]);
        C[c] -= 1;
    }
}

void sort(char A[][WORD_SIZE + 1], char B[][WORD_SIZE + 1]) {
    for (int d = WORD_SIZE - 1; d >= 0; --d) {
        countingSort(A, B, d);
    }
}

void printArray(char A[][WORD_SIZE + 1]) {
    for (int i = 1; i <= MAX_SIZE; ++i) {
        std::cout << A[i] << '\n';
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    char A[MAX_SIZE + 1][WORD_SIZE + 1] = {
        {'0', '0', '0', '\0'},
        {'3', '2', '9', '\0'},
        {'4', '5', '7', '\0'},
        {'6', '5', '7', '\0'},
        {'8', '3', '9', '\0'},
        {'4', '3', '6', '\0'},
        {'7', '2', '0', '\0'},
        {'3', '5', '5', '\0'}
    };
    
    char B[MAX_SIZE + 1][WORD_SIZE + 1];
    
    printArray(A);
    sort(A, B);
    printArray(B);
    
    return 0;
}
