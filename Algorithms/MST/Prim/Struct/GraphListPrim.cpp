// GraphListPrim.cpp
#include "GraphListPrim.h"
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <iostream>
#include "ctime"
#include "cmath"
#include <climits>

// Constructor
GraphListPrim::GraphListPrim(int vertices) : V(vertices) {
    adjacencyList.resize(V);
    std::srand(std::time(0)); // Initialize random number generator
}

// Add edge to the graph
void GraphListPrim::addEdge(int src, int dest, int weight) {
    adjacencyList[src].emplace_back(dest, weight);
    adjacencyList[dest].emplace_back(src, weight); // since the graph is undirected
}

// Generate a simple spanning tree
void GraphListPrim::generateSpanningTree() {
    std::vector<bool> visited(V, false);
    visited[0] = true;
    for (int i = 1; i < V; ++i) {
        int weight = std::rand() % 10 + 1; // random weight between 1-10
        addEdge(0, i, weight);
    }
}

// Generate additional edges based on density
void GraphListPrim::generateAdditionalEdges(double density) {
    int maxEdges = (V * (V - 1)) / 2;
    int targetEdges = std::round((density / 100.0) * maxEdges);
    int currentEdges = V - 1; // Since the spanning tree has exactly V-1 edges

    while (currentEdges < targetEdges) {
        int u = std::rand() % V;
        int v = std::rand() % V;
        if (u != v && !isEdgePresent(u, v)) {
            int weight = std::rand() % 10 + 1; // random weight between 1-10
            addEdge(u, v, weight);
            currentEdges++;
        }
    }
}

// Print the adjacency list
void GraphListPrim::printAdjacencyList() const {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : adjacencyList[i]) {
            std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

// Get all edges in the graph
std::vector<std::tuple<int, int, int>> GraphListPrim::getEdges() const {
    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < V; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            if (i < neighbor.first) { // To avoid duplicates in an undirected graph
                edges.emplace_back(i, neighbor.first, neighbor.second);
            }
        }
    }
    return edges;
}

// Check if an edge is present
bool GraphListPrim::isEdgePresent(int u, int v) const {
    for (const auto& neighbor : adjacencyList[u]) {
        if (neighbor.first == v) {
            return true;
        }
    }
    return false;
}

// Prim's algorithm to generate the MST
void GraphListPrim::primMST() const {
    using Edge = std::pair<int, int>; // (weight, destination)
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    std::vector<bool> inMST(V, false);
    std::vector<int> key(V, INT_MAX);
    std::vector<int> parent(V, -1);
    int totalWeight = 0;

    int src = 0; // Starting vertex
    key[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;
        totalWeight += weight;

        if (parent[u] != -1) {
            std::cout << "(" << parent[u] << ", " << u << ", " << weight << ")\n";
        }

        for (const auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!inMST[v] && key[v] > w) {
                key[v] = w;
                pq.emplace(w, v);
                parent[v] = u;
            }
        }
    }

    std::cout << "Calkowita waga MST: " << totalWeight << std::endl;
}