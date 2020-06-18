//
//  main.cpp
//  Disjoint Sets
//
//  Created by Alexis Quinto on 6/8/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

class Node {
public:
    int key;
    int rank;
    Node* parent;
    Node(int k) {
        key = k;
    }
};

void makeSet(Node* x) {
    x->parent = x;
    x->rank = 0;
}

void linkSet(Node* x, Node* y) {
    if (x->rank > y->rank) {
        y->parent = x;
    } else {
        x->parent = y;
        if (x->rank == y->rank)
            y->rank += 1;
    }
}

Node* findSet(Node* x) {
    if (x != x->parent)
        x->parent = findSet(x->parent);
    return x->parent;
}

void joinSet(Node* x, Node* y) {
    linkSet(findSet(x), findSet(y));
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    return 0;
}
