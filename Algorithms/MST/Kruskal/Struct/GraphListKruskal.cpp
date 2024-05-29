// GraphListPrim.cpp
#include "GraphListKruskal.h"
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <iostream>
#include "ctime"
#include "cmath"
#include <climits>
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <iostream>
#include <algorithm> // for std::sort
#include <numeric>   // for std::iota


// Constructor
GraphListKruskal::GraphListKruskal(int vertices) : V(vertices) {
    adjacencyList.resize(V);
    std::srand(std::time(0)); // Initialize random number generator
}

// Add edge to the graph
void GraphListKruskal::addEdge(int src, int dest, int weight) {
    adjacencyList[src].emplace_back(dest, weight);
    adjacencyList[dest].emplace_back(src, weight); // since the graph is undirected
}

// Generate a simple spanning tree
void GraphListKruskal::generateSpanningTree() {
    std::vector<bool> visited(V, false);
    visited[0] = true;
    for (int i = 1; i < V; ++i) {
        int weight = std::rand() % 10 + 1; // random weight between 1-10
        addEdge(0, i, weight);
    }
}

// Generate additional edges based on density
void GraphListKruskal::generateAdditionalEdges(double density) {
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
void GraphListKruskal::printAdjacencyList() const {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : adjacencyList[i]) {
            std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

// Get all edges in the graph
std::vector<std::tuple<int, int, int>> GraphListKruskal::getEdges() const {
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
bool GraphListKruskal::isEdgePresent(int u, int v) const {
    for (const auto& neighbor : adjacencyList[u]) {
        if (neighbor.first == v) {
            return true;
        }
    }
    return false;
}

// Helper function to find the parent of a vertex
int GraphListKruskal::findParent(std::vector<int>& parent, int vertex) const {
    if (parent[vertex] != vertex) {
        parent[vertex] = findParent(parent, parent[vertex]);
    }
    return parent[vertex];
}

// Helper function to perform union of two subsets
void GraphListKruskal::unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v) const {
    int uRoot = findParent(parent, u);
    int vRoot = findParent(parent, v);

    if (rank[uRoot] < rank[vRoot]) {
        parent[uRoot] = vRoot;
    } else if (rank[uRoot] > rank[vRoot]) {
        parent[vRoot] = uRoot;
    } else {
        parent[vRoot] = uRoot;
        rank[uRoot]++;
    }
}

void GraphListKruskal::kruskalMST() const {
    // Get all edges in the graph
    std::vector<std::tuple<int, int, int>> edges = getEdges();

    // Sort the edges based on their weights
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    std::vector<int> parent(V);
    std::vector<int> rank(V, 0);

    // Initialize parent array for disjoint set
    std::iota(parent.begin(), parent.end(), 0);

    std::vector<std::tuple<int, int, int>> mst; // Stores the MST edges
    int totalWeight = 0; // Total weight of MST

    for (const auto& edge : edges) {
        int u = std::get<0>(edge);
        int v = std::get<1>(edge);
        int weight = std::get<2>(edge);

        int uParent = findParent(parent, u);
        int vParent = findParent(parent, v);

        // Check if adding this edge creates a cycle
        if (uParent != vParent) {
            mst.emplace_back(u, v, weight);
            unionSets(parent, rank, uParent, vParent);
            totalWeight += weight;
        }
    }

    // Print the MST edges
    std::cout << "Minimum Spanning Tree (Kruskal's Algorithm):\n";
    for (const auto& edge : mst) {
        std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ", " << std::get<2>(edge) << ")\n";
    }

    // Print the total weight of MST
    std::cout << "Total Weight of MST: " << totalWeight << std::endl;
}