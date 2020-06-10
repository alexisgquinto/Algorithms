//
//  main.cpp
//  Chaining
//
//  Created by Alexis Quinto on 6/11/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0
#define MAX_SIZE 1000

class Node {
public:
    Node* next;
    Node* prev;
    int key;
    int satellite;
    
    Node(int k, int s) {
        key = k;
        satellite = s;
    }
};

class List {
public:
    Node* nil;
    
    List() {
        nil = new Node(-1, 0);
        nil->next = nil;
        nil->prev = nil;
    }
};

void insert(List* L, Node* x) {
    x->next = L->nil->next;
    L->nil->next->prev = x;
    x->prev = L->nil;
    L->nil->next = x;
}

Node* search(List* L, int k) {
    Node* x = L->nil->next;
    while(x->key != k && x != L->nil) {
        x = x->next;
    }
    return x;
}

void remove(Node* x) {
    x->next->prev = x->prev;
    x->prev->next = x->next;
}

int h(int k) {
    return k % MAX_SIZE;
}

void hashInsert(List** T, Node* x) {
    if (T[h(x->key)] == NIL)
        T[h(x->key)] = new List();
    insert(T[h(x->key)], x);
}

Node* hashSearch(List** T, int k) {
    if (T[h(k)] == NIL) return NIL;
    return search(T[h(k)], k);
}

void hashRemove(Node* x) {
    remove(x);
}

void initializeHT(List** T) {
    for (int i = 0; i < MAX_SIZE; ++i)
        T[i] = NIL;
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    List** T = new List*[MAX_SIZE];
    initializeHT(T);
    
    hashInsert(T, new Node(13, 1));
    hashInsert(T, new Node(20, 2));
    hashInsert(T, new Node(22, 3));
    hashInsert(T, new Node(33, 4));
    hashInsert(T, new Node(143, 5));
    hashInsert(T, new Node(1000000, 5));
    
    std::cout << "Search 143: " << hashSearch(T, 143)->satellite << '\n';
    std::cout << "Search 20: " << hashSearch(T, 20)->satellite << '\n';
    std::cout << "Search 13: " << hashSearch(T, 13)->satellite << '\n';
    std::cout << "Search 1000000: " << hashSearch(T, 1000000)->satellite << '\n';
    
    Node* x = hashSearch(T, 1);
    std::cout << "Search 1: " << (x == NIL ? NIL : x->satellite) << '\n';
    
    Node* y = hashSearch(T, 143);
    hashRemove(y);
    std::cout << "Search removed value = 143: " << hashSearch(T, 143)->satellite << '\n';
    
    return 0;
}
