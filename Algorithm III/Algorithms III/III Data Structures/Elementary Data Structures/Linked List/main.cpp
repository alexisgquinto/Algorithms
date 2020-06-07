//
//  main.cpp
//  Linked List
//
//  Created by Alexis Quinto on 6/6/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0

class Node {
public:
    int key;
    Node* next;
    Node* prev;
    
    Node(int k) {
        key = k;
    }
};

class List {
public:
    Node* nil;
    
    List() {
        nil = new Node(-1);
        nil->next = nil;
        nil->prev = nil;
    }
};

Node* search(List* L, int k) {
    Node* x = L->nil->next;
    while (x != L->nil && x->key != k)
        x = x->next;
    return x;
}

void insert(List* L, Node* x) {
    x->next = L->nil->next;
    L->nil->next->prev = x;
    x->prev = L->nil;
    L->nil->next = x;
}

void remove(List* L, Node* x) {
    x->next->prev = x->prev;
    x->prev->next = x->next;
}

void printList(List* L) {
    Node* x = L->nil->next;
    while(x != L->nil) {
        std::cout << x->key << " ";
        x = x->next;
    }
    std::cout << '\n';
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    List* L = new List();
    insert(L, new Node(3));
    insert(L, new Node(4));
    insert(L, new Node(33));
    insert(L, new Node(32));
    insert(L, new Node(23));
    insert(L, new Node(53));
    insert(L, new Node(73));
    insert(L, new Node(39));
    
    printList(L);
    
    std::cout << "Search 43: " << search(L, 43) << '\n'; // pointed to sentinel since 43 doesn't exist
    std::cout << "Search 33: " << search(L, 33) << '\n';
    std::cout << "Search 32: " << search(L, 32) << '\n';
    remove(L, search(L, 32));
    std::cout << "Search 32: " << search(L, 32) << '\n'; // pointed to sentinel since 32 doesn't exist
    return 0;
}
