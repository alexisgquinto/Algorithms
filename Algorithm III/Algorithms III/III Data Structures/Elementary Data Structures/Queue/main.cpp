//
//  main.cpp
//  Queue
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

class Queue {
public:
    Node* nil;
    
    Queue() {
        nil = new Node(-1);
        nil->next = nil;
        nil->prev = nil;
    }
};

void enqueue(Queue* Q, Node* x) {
    x->prev = Q->nil->prev;
    Q->nil->prev->next = x;
    x->next = Q->nil;
    Q->nil->prev = x;
}

Node* dequeue(Queue* Q) {
    Node* x = Q->nil->next;
    Q->nil->next = x->next;
    x->next->prev = Q->nil;
    return x;
}

void printQueue(Queue* Q) {
    Node* x = Q->nil->next;
    while (x != Q->nil) {
        std::cout << x->key << " ";
        x = x-> next;
    }
    std::cout << '\n';
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Queue* Q = new Queue();
    enqueue(Q, new Node(3));
    enqueue(Q, new Node(4));
    enqueue(Q, new Node(5));
    enqueue(Q, new Node(6));
    enqueue(Q, new Node(7));
    enqueue(Q, new Node(8));
    enqueue(Q, new Node(9));
    
    printQueue(Q);
    
    std::cout << "Dequeue: " << dequeue(Q)->key << '\n';
    std::cout << "Dequeue: " << dequeue(Q)->key << '\n';
    std::cout << "Dequeue: " << dequeue(Q)->key << '\n';
    
    printQueue(Q);
    
    return 0;
}
