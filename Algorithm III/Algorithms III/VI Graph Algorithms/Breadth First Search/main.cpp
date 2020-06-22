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
    int color;
    Node* parent;
    int d;
    Node(int k) {
        key = k;
        next = NIL;
        prev = NIL;
        d = 0;
        color = WHITE;
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

void addEdge(Graph* G, Node* u, Node* v, int s) {
    // connection from u to v
    if (G->Adj[u->key] == NIL)
        G->Adj[u->key] = new List();
    insert(G->Adj[u->key], v);
    
    if (G->V[u->key] == NIL) {
        G->V[u->key] = u;
        G->vertexCtr++;
    }
    
    if (G->V[v->key] == NIL) {
        G->V[v->key] = v;
        G->vertexCtr++;
    }
}

void bfs(Graph* G, Node* s) {
    for (int i = 0; i < MAX_V_SIZE; ++i) {
        if (G->V[i] != NIL && s != G->V[i]) {
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
            if (v->color == WHITE) {
                v->color = GRAY;
                v->d = u->d + 1;
                v->parent = u;
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
    addEdge(G, new Node(1), new Node(2), 0);
    addEdge(G, new Node(1), new Node(4), 0);
    addEdge(G, new Node(2), new Node(5), 0);
    addEdge(G, new Node(3), new Node(6), 0);
    addEdge(G, new Node(3), new Node(5), 0);
    addEdge(G, new Node(4), new Node(2), 0);
    addEdge(G, new Node(5), new Node(4), 0);
    addEdge(G, new Node(6), new Node(6), 0);
    
    bfs(G, G->V[1]);
    
    std::cout << "Shortest path from 1 to 6: ";
    printPath(G, G->V[1], G->V[6]);
    std::cout << '\n';
    
    std::cout << "Shortest path from 1 to 4: ";
    printPath(G, G->V[1], G->V[4]);
    std::cout << '\n';
    
    std::cout << "Shortest path from 1 to 5: ";
    printPath(G, G->V[1], G->V[5]);
    std::cout << '\n';
    return 0;
}
