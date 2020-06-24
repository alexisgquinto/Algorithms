//
//  main.cpp
//  Depth First Search
//
//  Created by Alexis Quinto on 6/25/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0
#define MAX_V_SIZE 6
#define WHITE 0
#define GRAY 1
#define BLACK 2

class Node {
public:
    Node* next;
    Node* prev;
    int key;
    int satellite;
    int d;
    int f;
    int color;
    Node* parent;
    Node(int k) {
        key = k;
        next = NIL;
        prev = NIL;
        satellite = 0;
        d = 0;
        f = 0;
        parent = NIL;
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

int globalTime;

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1];
    Node* V[MAX_V_SIZE + 1];
    Graph() {
        for (int i = 0; i <= MAX_V_SIZE; ++i) {
            Adj[i] = NIL;
            V[i] = NIL;
        }
    }
};

void addVertex(Graph* G, int u) {
    if (G->V[u] == NIL)
        G->V[u] = new Node(u);
}

void addEdge(Graph* G, int u, int v) {
    if (G->Adj[u] == NIL)
        G->Adj[u] = new List();
    insert(G->Adj[u], new Node(v));
}

void dfsVisit(Graph* G, Node* u) {
    globalTime++;
    u->d = globalTime;
    u->color = GRAY;
    
    List* L = G->Adj[u->key];
    Node* node = L->nil->next;
    while(node != L->nil) {
        Node* v = G->V[node->key];
        if (v->color == WHITE) {
            v->parent = u;
            dfsVisit(G, v);
        }
        node = node->next;
    }
    u->color = BLACK;
    globalTime++;
    u->f = globalTime;
}

void dfs(Graph* G) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        G->V[i]->color = WHITE;
        G->V[i]->parent = NIL;
    }
    globalTime = 0;
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        if (G->V[i]->color == WHITE)
            dfsVisit(G, G->V[i]);
}

void printPath(Graph* G, Node* s, Node* v) {
    if (v == s) {
        std::cout << s->key << " ";
    } else if (v->parent == NIL) {
        std::cout << "No path from " << s->key << " to " << v->key << " exists.";
    } else {
        printPath(G, s, v->parent);
        std::cout << v->key << " ";
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Graph* G = new Graph();
    
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        addVertex(G, i);
    }

    addEdge(G, 1, 2);
    addEdge(G, 1, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);
    addEdge(G, 3, 5);
    addEdge(G, 4, 2);
    addEdge(G, 5, 4);
    addEdge(G, 6, 6);
    
    dfs(G);
    
    std::cout << "Print start and finish time of visit per Vertex:" << '\n';
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        std::cout << i << ": " << G->V[i]->d << "/" << G->V[i]->f << '\n';
    }
    
    return 0;
}
