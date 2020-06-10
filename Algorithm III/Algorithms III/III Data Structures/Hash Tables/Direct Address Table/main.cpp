//
//  main.cpp
//  Direct Address Table
//
//  Created by Alexis Quinto on 6/10/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_SIZE 1000
#define NIL 0

class Node {
public:
    int key;
    int satellite;
    
    Node(int k, int s) {
        key = k;
        satellite = s;
    }
};

Node* search(Node* T[MAX_SIZE], int k) {
    return T[k];
}

void insert(Node* T[MAX_SIZE], Node* x) {
    T[x->key] = x;
}

void remove(Node* T[MAX_SIZE], Node* x) {
    T[x->key] = NIL;
}

void initializeHT(Node** T) {
    for (int i = 0; i < MAX_SIZE; ++i)
        T[i] = NIL;
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Node** T = new Node*[MAX_SIZE];
    initializeHT(T);
    
    insert(T, new Node(13, 1));
    insert(T, new Node(20, 2));
    insert(T, new Node(22, 3));
    insert(T, new Node(33, 4));
    insert(T, new Node(3, 5));
    
    std::cout << "Search 33: " << search(T, 33)->satellite << '\n';
    std::cout << "Search 20: " << search(T, 20)->satellite << '\n';
    std::cout << "Search 22: " << search(T, 22)->satellite << '\n';
    
    Node* x = search(T, 1);
    std::cout << "Search 1: " << (x == NIL ? NIL : x->satellite)  << '\n';
    
    remove(T, search(T, 22));
    Node* y = search(T, 22);
    std::cout << "Search the removed value = 22: "<< (y == NIL ? NIL : x->satellite)  << '\n';
    
    return 0;
}
