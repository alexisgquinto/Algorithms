//
//  main.cpp
//  Heap Sort
//
//  Created by Alexis Quinto on 6/6/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <limits.h>

#define PARENT(i) i/2
#define LEFT(i) i << 1
#define RIGHT(i) (i << 1) + 1
#define MAX_ARRAY_SIZE 10

class Heap {
public:
    int length = 10; // number of elements in the array
    int heapSize = 0; // number of elements in the heap within the array
    int A[MAX_ARRAY_SIZE + 1] = {0, 4, 2, 3, 5, 9, 7, 8, 9, 10, 10}; // sample data starts at index 1
};

void maxHeapify(Heap* A, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    
    int largest = i;
    if (l <= A->heapSize && A->A[l] > A->A[i])
        largest = l;
    if (r <= A->heapSize && A->A[r] > A->A[largest])
        largest = r;
    
    if (largest != i) {
        int tmp = A->A[i];
        A->A[i] = A->A[largest];
        A->A[largest] = tmp;
        maxHeapify(A, largest);
    }
}

void buildMaxHeap(Heap* A) {
    A->heapSize = A->length;
    for (int i = A->length/2; i >= 1; --i)
        maxHeapify(A, i);
}

void sort(Heap* A) {
    buildMaxHeap(A);
    for (int i = A->length; i >= 2; --i) {
        int tmp = A->A[1];
        A->A[1] = A->A[i];
        A->A[i] = tmp;
        A->heapSize -= 1;
        maxHeapify(A, 1);
    }
}

void printHeap(Heap* A) {
    for (int i = 1; i <= A->length; ++i) {
        std::cout << A->A[i] << " ";
    }
    std::cout << "\n";
}

int maximum(Heap* A) {
    return A->A[1];
}

int extractMaximum(Heap* A) {
    if (A->heapSize < 1) return -1; // no element inside the heap
    int maximum = A->A[1];
    A->A[1] = A->A[A->heapSize];
    A->A[A->heapSize] = 0; // reset to original value
    A->heapSize -= 1;
    maxHeapify(A, 1);
    return maximum;
}

void heapIncreaseKey(Heap* A, int key) {
    int i = A->heapSize;
    if (key < A->A[i])
        return; // new key is smaller than current key
    A->A[i] = key;
    while (i > 1 && A->A[PARENT(i)] < A->A[i]) {
        int tmp = A->A[i];
        A->A[i] = A->A[PARENT(i)];
        A->A[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

void maxHeapInsert(Heap* A, int key) {
    A->heapSize += 1;
    A->A[A->heapSize] = -INT_MIN;
    heapIncreaseKey(A, key);
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Heap* heap = new Heap();
    printHeap(heap);
    sort(heap);
    printHeap(heap);
    
    Heap* heap2 = new Heap();
    buildMaxHeap(heap2);
    std::cout << "Maximum: " << maximum(heap2) << '\n';
    std::cout << "Extract Maximum: " << extractMaximum(heap2) << '\n';
    std::cout << "Extract Maximum: " << extractMaximum(heap2) << '\n';
    std::cout << "Extract Maximum: " << extractMaximum(heap2) << '\n';
    std::cout << "Extract Maximum: " << extractMaximum(heap2) << '\n';
    std::cout << "New Maximum: " << maximum(heap2) << '\n';
    
    maxHeapInsert(heap2, 20);
    std::cout << "Maximum: " << maximum(heap2) << '\n';
    
    maxHeapInsert(heap2, 4);
    std::cout << "Maximum: " << maximum(heap2) << '\n';
    
    return 0;
}
