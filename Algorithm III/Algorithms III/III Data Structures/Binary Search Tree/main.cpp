//
//  main.cpp
//  Binary Search Tree
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
    
    Node(int k) {
        key = k;
        left = NIL;
        right = NIL;
        parent = NIL;
    }
};

class BST {
public:
    Node* root;
    
    BST() {
        root = NIL;
    }
};

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

void inorderTraversal(Node* x) {
    if (x != NIL) {
        inorderTraversal(x->left);
        std::cout << x->key << " ";
        inorderTraversal(x->right);
    }
}

Node* minimum(Node* x) {
    while(x->left != NIL)
        x = x->left;
    return x;
}

Node* maximum(Node* x) {
    while (x->right != NIL)
        x = x->right;
    return x;
}

Node* successor(Node* x) {
    if (x->right != NIL)
        return minimum(x->right);
    Node* y = x->parent;
    while(y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

Node* predecessor(Node* x) {
    if (x->left != NIL)
        return maximum(x->left);
    Node* y = x->parent;
    while(y != NIL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
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
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    BST* T = new BST();
    insert(T, new Node(12));
    insert(T, new Node(5));
    insert(T, new Node(18));
    insert(T, new Node(2));
    insert(T, new Node(9));
    insert(T, new Node(15));
    insert(T, new Node(19));
    insert(T, new Node(13));
    insert(T, new Node(17));
    
    inorderTraversal(T->root);
    
    std::cout << "\nSearch 13: " << search(T->root, 13) << '\n';
    std::cout << "Search 69: " << search(T->root, 69) << '\n'; // points to nil object of the T since 69 doesn't exist
    
    std::cout << "Minimum: " << minimum(T->root)->key << '\n';
    std::cout << "Maximum: " << maximum(T->root)->key << '\n';
    
    std::cout << "Successor of 17: " << successor(search(T->root, 17))->key << '\n';
    std::cout << "Successor of 12: " << successor(search(T->root, 12))->key << '\n';
    
    std::cout << "Predecessor of 13: " << predecessor(search(T->root, 13))->key << '\n';
    std::cout << "Predecessor of 12: " << predecessor(search(T->root, 12))->key << '\n';
    
    remove(T, search(T->root, 12));
    inorderTraversal(T->root);
    std::cout << '\n';
    
    return 0;
}
