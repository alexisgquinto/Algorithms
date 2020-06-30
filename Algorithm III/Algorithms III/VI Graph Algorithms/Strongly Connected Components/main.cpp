//
//  main.cpp
//  Strongly Connected Components
//
//  Created by Alexis Quinto on 6/28/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <vector>

#define NIL 0
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_V_SIZE 8

using namespace std;

class Vertex {
public:
    int key;
    int color;
    int d;
    int f;
    Vertex* parent;
    Vertex(int k) {
        key = k;
        color = WHITE;
        d = 0;
        f = 0;
        parent = NIL;
    }
};

class Node {
public:
    Node* next;
    Node* prev;
    int key;
    Node(int k) {
        key = k;
        next = NIL;
        prev = NIL;
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

void insert(List* L, Node* x) {
    x->next = L->nil->next;
    L->nil->next->prev = x;
    x->prev = L->nil;
    L->nil->next = x;
}

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1] = {};
    Vertex* V[MAX_V_SIZE + 1] = {};
};

void addVertex(Graph* G, int u) {
    if (G->V[u] == NIL)
        G->V[u] = new Vertex(u);
}

void addEdge(Graph* G, int u, int v) {
    List* L = G->Adj[u];
    if (L == NIL)
        L = new List();
    insert(L, new Node(v));
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    Graph* G = new Graph();
    
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        addVertex(G, i);
    
    addEdge(G, 1, 2);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 2, 3);
    addEdge(G, 3, 7);
    addEdge(G, 3, 4);
    addEdge(G, 4, 3);
    addEdge(G, 4, 8);
    addEdge(G, 5, 1);
    addEdge(G, 5, 6);
    addEdge(G, 6, 7);
    addEdge(G, 7, 6);
    addEdge(G, 7, 8);
    addEdge(G, 8, 8);
    
    return 0;
}
