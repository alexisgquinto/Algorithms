//
//  main.cpp
//  Stack
//
//  Created by Alexis Quinto on 6/7/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

class Node {
public:
    int key;
    Node* next;
    Node* prev;
    
    Node(int k) {
        key = k;
    }
};

class Stack {
public:
    Node* nil;
    
    Stack() {
        nil = new Node(-1);
        nil->next = nil;
        nil->prev = nil;
    }
};

void push(Stack* S, Node* x) {
    x->next = S->nil->next;
    S->nil->next->prev = x;
    x->prev = S->nil;
    S->nil->next = x;
}

Node* pop(Stack* S) {
    Node* x = S->nil->next;
    S->nil->next = x->next;
    x->prev = S->nil;
    return x;
}

void printStack(Stack* S) {
    Node* x = S->nil->next;
    while (x != S->nil) {
        std::cout << x->key << " ";
        x = x-> next;
    }
    std::cout << '\n';
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Stack* S = new Stack();
    push(S, new Node(3));
    push(S, new Node(4));
    push(S, new Node(5));
    push(S, new Node(6));
    push(S, new Node(7));
    push(S, new Node(8));
    
    printStack(S);
    
    std::cout << "Pop: " << pop(S)->key << '\n';
    std::cout << "Pop: " << pop(S)->key << '\n';
    std::cout << "Pop: " << pop(S)->key << '\n';
    std::cout << "Pop: " << pop(S)->key << '\n';
    
    printStack(S);
    
    return 0;
}
