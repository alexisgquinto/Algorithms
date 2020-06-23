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

class Node {
public:
    Node* next;
    Node* prev;
    int key;
    int satellite;
    int color;
    int d;
    Node* parent;
    Node(int k) {
        next = NIL;
        prev = NIL;
        key = k;
        satellite = 0;
        color = WHITE;
        d = 0;
        parent = NIL;
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

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1]; // Adjacency list
    
    int vertexCtr;
    Node* V[MAX_V_SIZE + 1]; // Array of vertices
    
    Graph() {
        vertexCtr = 0;
        for (int i = 0; i <= MAX_V_SIZE; ++i) {
            Adj[i] = NIL;
            V[i] = NIL;
        }
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
}

void bfs(Graph* G, Node* s) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        if (G->V[i] != NIL) {
            G->V[i]->color = WHITE;
            G->V[i]->parent = NIL;
            G->V[i]->d = INT_MAX;
        }
    }
    s->color = GRAY;
    s->d = 0;
    s->parent = NIL;
    
    std::queue<Node*> Q;
    Q.push(s);
    while(!Q.empty()) {
        Node* u = Q.front();
        Q.pop();
        
        Node* v = G->Adj[u->key]->nil->next;
        while (v != G->Adj[u->key]->nil) {
            if (G->V[v->key]->color == WHITE) {
                G->V[v->key]->color = GRAY;
                G->V[v->key]->d = G->V[u->key]->d + 1;
                G->V[v->key]->parent = G->V[u->key];
                Q.push(v);
            }
            v = v->next;
        }
        u->color = BLACK;
    }
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
