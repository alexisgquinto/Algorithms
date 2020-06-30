//
//  main.cpp
//  Topological Sort
//
//  Created by Alexis Quinto on 6/26/20.
//  Copyright © 2020 Alexis Quinto. All rights reserved.
//

#include <iostream>

#define NIL 0
#define MAX_V_SIZE 9
#define WHITE 0
#define GRAY 1
#define BLACK 2

class Vertex {
public:
    int key;
    char* satellite;
    int d;
    int f;
    int color;
    Vertex* parent;
    Vertex(int k) {
        key = k;
        satellite = NIL;
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

int globalTime;

class Graph {
public:
    List* Adj[MAX_V_SIZE + 1] = {};
    Vertex* V[MAX_V_SIZE + 1] = {};
};

void addVertex(Graph* G, int u, char* s) {
    if (G->V[u] == NIL) {
        G->V[u] = new Vertex(u);
        G->V[u]->satellite = s;
    }
}

void addEdge(Graph* G, int u, int v) {
    if (G->Adj[u] == NIL)
        G->Adj[u] = new List();
    insert(G->Adj[u], new Node(v));
}

void dfsVisit(Graph* G, Vertex* u, List* L) {
    globalTime++;
    u->d = globalTime;
    u->color = GRAY;
    
    List* adjL = G->Adj[u->key];
    if (adjL != NIL) {
        Node* node = adjL->nil->next;
        while(node != adjL->nil) {
            Vertex* v = G->V[node->key];
            if (v->color == WHITE) {
                v->parent = u;
                dfsVisit(G, v, L);
            }
            node = node->next;
        }
    }
    u->color = BLACK;
    globalTime++;
    u->f = globalTime;
    insert(L, new Node(u->key));
}

void dfs(Graph* G, List* L) {
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        G->V[i]->color = WHITE;
        G->V[i]->parent = NIL;
    }
    globalTime = 0;
    for (int i = 1; i <= MAX_V_SIZE; ++i)
        if (G->V[i]->color == WHITE)
            dfsVisit(G, G->V[i], L);
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

void printList(Graph* G, List* L) {
    if (L == NIL) return;
    Node* x = L->nil->next;
    while(x != L->nil) {
        std::cout << G->V[x->key]->satellite << " ";
        x = x->next;
    }
}

List* topologicalSort(Graph* G) {
    List* L = new List();
    dfs(G, L);
    return L;
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    Graph* G = new Graph();
    char* str[MAX_V_SIZE + 1] = {
        "",
        "shirt",
        "tie",
        "jacket",
        "watch",
        "undershorts",
        "pants",
        "belt",
        "socks",
        "shoes"
    };
    
    for (int i = 1; i <= MAX_V_SIZE; ++i) {
        addVertex(G, i, str[i]);
    }

    addEdge(G, 1, 7);
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 5, 9);
    addEdge(G, 5, 6);
    addEdge(G, 6, 9);
    addEdge(G, 6, 7);
    addEdge(G, 7, 3);
    addEdge(G, 8, 9);
    
    printList(G, topologicalSort(G));
    std::cout << '\n';
    
    return 0;
}
