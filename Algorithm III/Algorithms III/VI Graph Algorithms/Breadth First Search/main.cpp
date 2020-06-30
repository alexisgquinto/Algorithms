//
//  main.cpp
//  Breadth First Search
//
//  Created by Alexis Quinto on 6/22/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>
#include <queue>
#include <limits.h>

#define MAX_V_SIZE 6
#define NIL 0
#define WHITE 0
#define GRAY 1
#define BLACK 2

class Vertex {
public:
    int key;
    int satellite;
    int color;
    int d;
    Vertex* parent;
    Vertex(int k) {
        key = k;
        satellite = 0;
        color = WHITE;
        d = 0;
        parent = NIL;
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

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1] = {}; // Adjacency list
    Vertex* V[MAX_V_SIZE + 1] = {}; // Array of vertices
};

void addVertex(Graph* G, int k) {
    if (G->V[k] == NIL)
        G->V[k] = new Vertex(k);
}

void addEdge(Graph* G, int u, int v) {
    if (G->Adj[u] == NIL)
        G->Adj[u] = new List();
    insert(G->Adj[u], new Vertex(v));
}

void bfs(Graph* G, Vertex* s) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        Vertex* u = G->V[i];
        if (u != NIL) {
            u->color = WHITE;
            u->parent = NIL;
            u->d = INT_MAX;
        }
    }
    s->color = GRAY;
    s->d = 0;
    s->parent = NIL;
    
    std::queue<int> Q;
    Q.push(s->key);
    while(!Q.empty()) {
        Vertex* u = G->V[Q.front()];
        Q.pop();
        
        List* L = G->Adj[u->key];
        Vertex* node = L->nil->next;
        while (node != L->nil) {
            Vertex* v = G->V[node->key];
            if (v->color == WHITE) {
                v->color = GRAY;
                v->d = u->d + 1;
                v->parent = u;
                Q.push(v->key);
            }
            node = node->next;
        }
        u->color = BLACK;
    }
}

void printPath(Graph* G, Vertex* s, Vertex* v) {
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
    
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        addVertex(G, i);

    addEdge(G, 1, 2);
    addEdge(G, 1, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);
    addEdge(G, 3, 5);
    addEdge(G, 4, 2);
    addEdge(G, 5, 4);
    addEdge(G, 6, 6);
    
    bfs(G, G->V[3]);
    std::cout << "Shortest path from 3 to 2: ";
    printPath(G, G->V[3], G->V[2]);
    std::cout << "| distance = " << G->V[2]->d << '\n';
    
    bfs(G, G->V[1]);
    std::cout << "Shortest path from 1 to 6: ";
    printPath(G, G->V[1], G->V[6]);
    std::cout << '\n';

    std::cout << "Shortest path from 1 to 4: ";
    printPath(G, G->V[1], G->V[4]);
    std::cout << "| distance = " << G->V[4]->d << '\n';

    std::cout << "Shortest path from 1 to 5: ";
    printPath(G, G->V[1], G->V[5]);
    std::cout << "| distance = " << G->V[5]->d << '\n';
    
    return 0;
}
