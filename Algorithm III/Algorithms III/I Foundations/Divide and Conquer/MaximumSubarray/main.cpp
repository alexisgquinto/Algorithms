//
//  main.cpp
//  MaximumSubarray
//
//  Created by Alexis Quinto on 6/4/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#include <limits.h>

#define MAX_SIZE 16

class Subarray {
public:
    int left; // left index
    int right; // right index
    int sum; // sum of the subarray
    
    Subarray(int l, int r, int s) : left(l), right(r), sum(s) {};
};

Subarray* findMaxCrossingSubarray(int A[], int p, int q, int r) {
    int left = 0;
    int right = 0;
    int leftSum = INT_MIN;
    int rightSum = INT_MIN;
    int tmpSum = 0;
    
    for (int i = q; i >= p; --i) {
        tmpSum += A[i];
        if (leftSum < tmpSum) {
            left = i;
            leftSum = tmpSum;
        }
    }
    
    tmpSum = 0;
    for (int j = q + 1; j <= r; ++j) {
        tmpSum += A[j];
        if (rightSum < tmpSum) {
            right = j;
            rightSum = tmpSum;
        }
    }
    
    return new Subarray(left, right, leftSum + rightSum);
}

Subarray* findMaxSubarray(int A[], int p, int r) {
    if (r == p) {
        return new Subarray(p, r, A[p]);
    } else {
        int q = p + ((r - p) / 2);
        
        Subarray* leftSubarray = findMaxSubarray(A, p, q);
        Subarray* rightSubarray = findMaxSubarray(A, q + 1, r);
        Subarray* crossSubarray = findMaxCrossingSubarray(A, p, q, r);
        
        int leftSum = leftSubarray->sum;
        int rightSum = rightSubarray->sum;
        int crossSum = crossSubarray->sum;
        
        if (leftSum >= rightSum && leftSum >= crossSum) {
            return leftSubarray;
        } else if (rightSubarray->sum >= leftSum && rightSum >= crossSum) {
            return rightSubarray;
        } else {
            return crossSubarray;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    int A[MAX_SIZE + 1] = {0, 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    Subarray* sArray = findMaxSubarray(A, 1, 16);
    std::cout << "Max Subarray Sum = " << sArray->sum << "\n";
    return 0;
}
