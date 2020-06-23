//
//  main.cpp
//  Graph Representation
//
//  Created by Alexis Quinto on 6/21/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define MAX_V_SIZE 6
#define MAX_E_SIZE 6
#define NIL 0

// Adjacency List is usually method of choice for representing sparse graph
// Adjacency Matrix is preferred when graph is dense meaning |E| is nearly V^2 or
// if we need to tell quickly if there is an edge connecting given two vertices

class Node {
public:
    Node* next;
    Node* prev;
    int key;
    int satellite;
    Node(int k) {
        next = NIL;
        prev = NIL;
        key = k;
        satellite = 0;
    }
};

class Edge {
public:
    Node* u;
    Node* v;
    int satellite;
    Edge(Node* u, Node* v) {
        this->u = u;
        this->v = v;
        satellite = 0;
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

void printList(List* L) {
    if (L == NIL) return;
    Node* x = L->nil->next;
    while(x != L->nil) {
        std::cout << x->key << " ";
        x = x->next;
    }
}

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1]; // Adjacency list
    
    int vertexCtr;
    Node* V[MAX_V_SIZE + 1]; // Array of vertices
    
    int edgeCtr;
    Edge* E[MAX_E_SIZE * MAX_E_SIZE + 1]; // Array of edges
    
    Graph() {
        vertexCtr = 0;
        for (int i = 0; i <= MAX_V_SIZE; ++i) {
            Adj[i] = NIL;
            V[i] = NIL;
        }
        edgeCtr = 0;
        for (int i = 0; i <= MAX_E_SIZE; ++i)
            E[i] = NIL;
    }
};

void addVertex(Graph* G, int k, int s) {
    if (G->V[k] == NIL) {
        G->V[k] = new Node(k);
        G->V[k]->satellite = s;
        G->vertexCtr++;
    }
}

void addEdge(Graph* G, int u, int v) {
    // connection from u to v
    if (G->Adj[u] == NIL)
        G->Adj[u] = new List();
    insert(G->Adj[u], new Node(v));
    
    //connection from v to u
    if (G->Adj[v] == NIL)
        G->Adj[v] = new List();
    insert(G->Adj[v], new Node(u));
    
    G->E[G->edgeCtr++] = new Edge(new Node(u), new Node(v));
}

void printGraph(Graph* G) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        std::cout << i << ": ";
        printList(G->Adj[i]);
        std::cout << '\n';
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Graph* G = new Graph();
    
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        addVertex(G, i, 0);
    }

    addEdge(G, 1, 2);
    addEdge(G, 1, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);
    addEdge(G, 3, 5);
    addEdge(G, 4, 2);
    addEdge(G, 5, 4);
    addEdge(G, 6, 6);
    
    printGraph(G);
    
    return 0;
}
