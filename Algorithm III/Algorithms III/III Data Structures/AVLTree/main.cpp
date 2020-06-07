//
//  main.cpp
//  AVLTree
//
//  Created by Alexis Quinto on 6/7/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    
    Node(int k) {
        key = k;
        left = NIL;
        right = NIL;
        parent = NIL;
        height = 0;
    }
};

class BST {
public:
    Node* root;
    
    BST() {
        root = NIL;
    }
};

int height(Node* z) {
    if (z == NIL) return -1;
    return z->height;
}

void updateHeight(Node* z) {
    z->height = std::max(height(z->left), height(z->right)) + 1;
}

void rightRotate(BST* T, Node* x) {
    Node* y = x->left;
    y->parent = x->parent;
    if (y->parent == NIL) {
        T->root = y;
    } else {
        if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    x->left = y->right;
    if (x->left != NIL)
        x->left->parent = x;
    x->parent = y;
    y->right = x;
    updateHeight(x);
    updateHeight(y);
}

void leftRotate(BST* T, Node* x) {
    Node* y = x->right;
    y->parent = x->parent;
    if (y->parent == NIL) {
        T->root = y;
    } else {
        if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }
    x->right = y->left;
    if (x->right != NIL)
        x->right->parent = x;
    x->parent = y;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
}

void rebalance(BST* T, Node* z) {
    while(z != NIL) {
        updateHeight(z);
        if (height(z->left) >= 2 + height(z->right)) { // left heavy
            if (height(z->left->left) >= height(z->left->right)) {
                rightRotate(T, z);
            } else {
                leftRotate(T, z->left);
                rightRotate(T, z);
            }
        } else if (height(z->right) >= 2 + height(z->left)) {
            if (height(z->right->right) >= height(z->right->left)) {
                leftRotate(T, z);
            } else {
                rightRotate(T, z->right);
                leftRotate(T, z);
            }
        }
        z = z->parent;
    }
}

void insert(BST* T, Node* z) {
    Node* y = NIL;
    Node* x = T->root;
    while(x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NIL) {
        T->root = z; // tree T was empty
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    rebalance(T, z);
}

Node* search(Node* x, int k) {
    while(x != NIL && k != x->key) {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node* minimum(Node* x) {
    while(x->left != NIL)
        x = x->left;
    return x;
}

void transplant(BST* T, Node* u, Node* v) {
    if (u->parent == NIL) {
        T->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NIL)
        v->parent = u->parent;
}

void remove(BST* T, Node* z) {
    if (z->left == NIL) {
        transplant(T, z, z->right);
    } else if (z->right == NIL) {
        transplant(T, z, z->left);
    } else {
        Node* y = minimum(z->right);
        if (y->parent != z) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    rebalance(T, z->parent);
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    BST* T = new BST();
    insert(T, new Node(13));
    insert(T, new Node(12));
    insert(T, new Node(11));
    insert(T, new Node(10));
    insert(T, new Node(9));
    insert(T, new Node(8));
    insert(T, new Node(7));
    insert(T, new Node(6));
    insert(T, new Node(5));
    insert(T, new Node(4));
    insert(T, new Node(3));
    insert(T, new Node(2));
    insert(T, new Node(1));
    
    return 0;
}
