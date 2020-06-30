//
//  main.cpp
//  Disjoint Sets
//
//  Created by Alexis Quinto on 6/8/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0
#define MAX_V_SIZE 10

class Vertex {
public:
    int key;
    int rank;
    Vertex* parent;
    Vertex(int k) {
        key = k;
    }
};

void makeSet(Vertex* x) {
    x->parent = x;
    x->rank = 0;
}

void linkSet(Vertex* x, Vertex* y) {
    if (x->rank > y->rank) {
        y->parent = x;
    } else {
        x->parent = y;
        if (x->rank == y->rank)
            y->rank += 1;
    }
}

Vertex* findSet(Vertex* x) {
    if (x != x->parent)
        x->parent = findSet(x->parent);
    return x->parent;
}

void joinSet(Vertex* x, Vertex* y) {
    linkSet(findSet(x), findSet(y));
}

class Graph {
public:
    int Adj[MAX_V_SIZE + 1][MAX_V_SIZE + 1] = {};
    Vertex* V[MAX_V_SIZE + 1] = {};
};

void addVertex(Graph* G, int u) {
    if (G->V[u] == NIL)
        G->V[u] = new Vertex(u);
}

void addEdge(Graph* G, int u, int v) {
    G->Adj[u][v] = 1;
    G->Adj[v][u] = 1;
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Graph* G = new Graph();
    
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        addVertex(G, i);
        makeSet(G->V[i]);
    }
    
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 1);
    addEdge(G, 2, 4);
    addEdge(G, 5, 6);
    addEdge(G, 5, 7);
    addEdge(G, 8, 9);
    
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        for (int j = 1; j <= MAX_V_SIZE; ++j)
            if (G->Adj[i][j] == 1)
                if (findSet(G->V[i]) != findSet(G->V[j]))
                    joinSet(G->V[i], G->V[j]);
    
    std::cout << "Connected Components: " << '\n';
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        Vertex* u = G->V[i];
        std::cout << "Root from the set of vertex [" << i << "] is [" << findSet(u)->key << "]\n";
    }
    
    return 0;
}
