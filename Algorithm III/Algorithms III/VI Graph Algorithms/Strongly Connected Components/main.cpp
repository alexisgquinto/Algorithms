//
//  main.cpp
//  Strongly Connected Components
//
//  Created by Alexis Quinto on 6/28/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>

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
    int rank;
    Vertex* parent;
    Vertex(int k) {
        key = k;
        color = WHITE;
        d = 0;
        f = 0;
        parent = NIL;
        rank = 0;
    }
};

class Graph {
public:
    int Adj[MAX_V_SIZE + 1][MAX_V_SIZE + 1] = {};
    Vertex* V[MAX_V_SIZE + 1] = {};
};

void addVertex(Graph* G, Graph* GT, int u) {
    if (G->V[u] == NIL)
        G->V[u] = new Vertex(u);
    if (GT->V[u] == NIL)
        GT->V[u] = new Vertex(u);
}

void addEdge(Graph* G, Graph* GT, int u, int v) {
    G->Adj[u][v] = 1;
    GT->Adj[v][u] = 1;
}

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

int globalTime;

void dfsVisit(Graph* G, int u, stack<int>* st) {
    globalTime++;
    G->V[u]->d = globalTime;
    G->V[u]->color = GRAY;
    
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        if (G->Adj[u][i] == 1 && G->V[i]->color == WHITE)
            dfsVisit(G, i, st);
    
    globalTime++;
    G->V[u]->f = globalTime;
    G->V[u]->color = BLACK;
    st->push(u);
}

void dfs(Graph* G, stack<int>* st) {
    globalTime = 0;
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        G->V[i]->color = WHITE;
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        if (G->V[i]->color == WHITE)
            dfsVisit(G, i, st);
}

void dfs2Visit(Graph* G, Graph* GT, int uIndex, int repIndex) {
    Vertex* u = G->V[uIndex];
    Vertex* rep = G->V[repIndex];
    joinSet(u, rep);
    
    GT->V[uIndex]->color = GRAY;
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        if (GT->Adj[u->key][i] == 1 && GT->V[i]->color == WHITE)
            dfs2Visit(G, GT, i, repIndex);
    GT->V[uIndex]->color = BLACK;
}

void dfs2(Graph* G, Graph* GT, stack<int>* st) {
    while(!st->empty()) {
        int repIndex = st->top();
        st->pop();
        if (GT->V[repIndex]->color == WHITE)
            dfs2Visit(G, GT, repIndex, repIndex);
    }
}

int main(int argc, const char * argv[]) {
    cout << "Hello, World!\n";
    Graph* G = new Graph();
    Graph* GT = new Graph();
    stack<int>* st = new stack<int>();
    
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        addVertex(G, GT, i);
        makeSet(G->V[i]);
    }
    
    addEdge(G, GT,  1, 2);
    addEdge(G, GT,  2, 5);
    addEdge(G, GT,  2, 6);
    addEdge(G, GT,  2, 3);
    addEdge(G, GT,  3, 7);
    addEdge(G, GT,  3, 4);
    addEdge(G, GT,  4, 3);
    addEdge(G, GT,  4, 8);
    addEdge(G, GT,  5, 1);
    addEdge(G, GT,  5, 6);
    addEdge(G, GT,  6, 7);
    addEdge(G, GT,  7, 6);
    addEdge(G, GT,  7, 8);
    addEdge(G, GT,  8, 8);
    
    dfs(G, st);
    dfs2(G, GT, st);
    
    cout << "Strongly Connected Components:" << '\n';
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        cout << i << ": " << findSet(G->V[i])->key << '\n';
    
    return 0;
}
