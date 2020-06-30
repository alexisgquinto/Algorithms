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

class Vertex {
public:
    int key;
    int satellite;
    Vertex(int k) {
        key = k;
        satellite = 0;
    }
};

class Edge {
public:
    Vertex* u;
    Vertex* v;
    int satellite;
    Edge(Vertex* u, Vertex* v) {
        this->u = u;
        this->v = v;
        satellite = 0;
    }
};

class Vertex {
public:
    Vertex* next;
    Vertex* prev;
    int key;
    Vertex(int k) {
        next = NIL;
        prev = NIL;
        key = k;
    }
};

class List {
public:
    Vertex* nil;
    List() {
        nil = new Vertex(-1);
        nil->next = nil;
        nil->prev = nil;
    }
};

void insert(List* L, Vertex* x) {
    x->next = L->nil->next;
    L->nil->next->prev = x;
    x->prev = L->nil;
    L->nil->next = x;
}

void printList(List* L) {
    if (L == NIL) return;
    Vertex* x = L->nil->next;
    while(x != L->nil) {
        std::cout << x->key << " ";
        x = x->next;
    }
}

class Graph {
public:
    int vertexCtr = 0;
    int edgeCtr = 0;
    Vertex* V[MAX_V_SIZE + 1] = {}; // Array of vertices
    Edge* E[MAX_E_SIZE * MAX_E_SIZE + 1] = {}; // Array of edges
    List* Adj[MAX_V_SIZE + 1] = {}; // Adjacency list
};

void addVertex(Graph* G, int k, int s) {
    if (G->V[k] == NIL) {
        G->V[k] = new Vertex(k);
        G->V[k]->satellite = s;
        G->vertexCtr++;
    }
}

void addEdge(Graph* G, int u, int v) {
    // connection from u to v
    if (G->Adj[u] == NIL)
        G->Adj[u] = new List();
    insert(G->Adj[u], new Vertex(v));
    
    //connection from v to u
    if (G->Adj[v] == NIL)
        G->Adj[v] = new List();
    insert(G->Adj[v], new Vertex(u));
    
    G->E[G->edgeCtr++] = new Edge(new Vertex(u), new Vertex(v));
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
