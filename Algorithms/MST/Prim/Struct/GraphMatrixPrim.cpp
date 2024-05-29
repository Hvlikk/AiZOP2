// GraphMatrixPrim.cpp
#include "GraphMatrixPrim.h"
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <iostream>
#include <climits>

// Constructor
GraphMatrixPrim::GraphMatrixPrim(int vertices, int edges) : V(vertices), E(edges) {
    incidenceMatrix.resize(V, std::vector<int>(2 * E, 0)); // Allocate twice the number of edges
}

// Add edge to the graph
void GraphMatrixPrim::addEdge(int edgeIndex, int vertex1, int vertex2, int weight) {
    incidenceMatrix[vertex1][edgeIndex] = weight;
    incidenceMatrix[vertex2][edgeIndex] = weight;

    // Also add the edge in the reverse direction for undirected graph
    incidenceMatrix[vertex1][edgeIndex + 1] = weight;
    incidenceMatrix[vertex2][edgeIndex + 1] = weight;
}

// Set multiple edges in the graph
void GraphMatrixPrim::setEdges(const std::vector<std::tuple<int, int, int>>& edges) {
    int edgeIndex = 0;
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        addEdge(edgeIndex++, u, v, weight);
        edgeIndex++;
    }
}

// Print the incidence matrix
void GraphMatrixPrim::printIncidenceMatrix() const {
    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

// Prim's algorithm to generate the MST
void GraphMatrixPrim::primMST() const {
    using Edge = std::tuple<int, int, int>; // (weight, vertex1, vertex2)
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

    std::vector<bool> inMST(V, false);
    int totalWeight = 0;

    int src = 0; // Starting vertex
    inMST[src] = true;

    // Add all edges from the source vertex to the priority queue
    for (int j = 0; j < 2 * E; ++j) { // Iterate over doubled edges
        if (incidenceMatrix[src][j] != 0) {
            for (int v = 0; v < V; ++v) {
                if (v != src && incidenceMatrix[v][j] != 0) {
                    pq.emplace(incidenceMatrix[src][j], src, v);
                    break;
                }
            }
        }
    }

    while (!pq.empty()) {
        auto [weight, u, v] = pq.top();
        pq.pop();

        if (inMST[v]) {
            continue;
        }

        inMST[v] = true;
        totalWeight += weight;
        std::cout << "(" << u << ", " << v << ", " << weight << ")\n";

        // Add all edges from the newly added vertex to the priority queue
        for (int j = 0; j < 2 * E; ++j) { // Iterate over doubled edges
            if (incidenceMatrix[v][j] != 0) {
                for (int w = 0; w < V; ++w) {
                    if (w != v && incidenceMatrix[w][j] != 0 && !inMST[w]) {
                        pq.emplace(incidenceMatrix[v][j], v, w);
                        break;
                    }
                }
            }
        }
    }

    std::cout << "Calkowita waga MST: " << totalWeight << std::endl;
}