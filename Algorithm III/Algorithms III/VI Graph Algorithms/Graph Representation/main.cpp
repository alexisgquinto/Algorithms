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
    Node(int k) {
        key = k;
        next = NIL;
        prev = NIL;
    }
};

class Edge {
public:
    Node* u;
    Node* v;
    int satellite;
    Edge(Node* u, Node* v, int s) {
        this->u = u;
        this->v = v;
        satellite = s;
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
    List* V[MAX_V_SIZE + 1]; // Adjacency list
    Edge* E[MAX_E_SIZE * MAX_E_SIZE + 1]; // Array of edges
    int edgeCtr;
    Graph() {
        for (int i = 1; i <= MAX_V_SIZE; ++i) {
            V[i] = NIL;
        }
        for (int i = 0; i <= MAX_E_SIZE; ++i) {
            E[i] = NIL;
        }
        edgeCtr = 0;
    }
};

void addEdge(Graph* G, Node* u, Node* v, int s) {
    // connection from u to v
    if (G->V[u->key] == NIL)
        G->V[u->key] = new List();
    insert(G->V[u->key], v);
    
    //connection from v to u
    /* Uncomment if you want bi-directional graph
     if (G->V[v->key] == NIL)
        G->V[v->key] = new List();
     insert(G->V[v->key], u);
     */
    
    G->E[G->edgeCtr++] = new Edge(u, v, s);
}

void printGraph(Graph* G) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        std::cout << i << ": ";
        printList(G->V[i]);
        std::cout << '\n';
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Graph* G = new Graph();
    addEdge(G, new Node(1), new Node(2), 0);
    addEdge(G, new Node(1), new Node(4), 0);
    addEdge(G, new Node(2), new Node(5), 0);
    addEdge(G, new Node(3), new Node(6), 0);
    addEdge(G, new Node(3), new Node(5), 0);
    addEdge(G, new Node(4), new Node(2), 0);
    addEdge(G, new Node(5), new Node(4), 0);
    addEdge(G, new Node(6), new Node(6), 0);
    
    printGraph(G);
    
    return 0;
}
