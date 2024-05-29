#include "GraphMatrixKruskal.h"
#include <vector>
#include <tuple>
#include <algorithm> // for std::sort
#include <numeric>   // for std::iota
#include <iostream>

GraphMatrixKruskal::GraphMatrixKruskal(int vertices, int edges) : V(vertices), E(edges) {
    incidenceMatrix.resize(V, std::vector<int>(E, 0)); // Allocate twice the number of edges
}

// Add edge to the graph
void GraphMatrixKruskal::addEdge(int edgeIndex, int vertex1, int vertex2, int weight) {
    incidenceMatrix[vertex1][edgeIndex] = weight;
    incidenceMatrix[vertex2][edgeIndex] = weight;

    // Also add the edge in the reverse direction for undirected graph
    //incidenceMatrix[vertex1][edgeIndex + 1] = weight;
    //incidenceMatrix[vertex2][edgeIndex + 1] = weight;
}

// Set multiple edges in the graph
void GraphMatrixKruskal::setEdges(const std::vector<std::tuple<int, int, int>>& edges) {
    int edgeIndex = 0;
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        addEdge(edgeIndex, u, v, weight);
        edgeIndex++;
    }
}

// Print the incidence matrix
void GraphMatrixKruskal::printIncidenceMatrix() const {
    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int GraphMatrixKruskal::find(int parent[], int i) const {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

// Perform union of two sets
void GraphMatrixKruskal::Union(int parent[], int x, int y) const {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}


// Prim's algorithm to generate the MST
void GraphMatrixKruskal::kruskalMST() const {
    // Vector to store the edges of the MST
    std::vector<std::tuple<int, int, int>> result;

    // Create a vector to store the edges with their weights
    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < V; ++i) {
        for (int j = i + 1; j < V; ++j) {
            if (incidenceMatrix[i][j] != 0) {
                edges.push_back(std::make_tuple(incidenceMatrix[i][j], i, j));
            }
        }
    }

    // Sort the edges based on their weights
    std::sort(edges.begin(), edges.end());

    // Allocate memory for creating V subsets
    int *parent = new int[V];
    std::fill(parent, parent + V, -1);

    // Number of edges to be taken is equal to V-1
    int edgeCount = 0;
    for (const auto& edge : edges) {
        if (edgeCount == V - 1)
            break;

        int u, v, weight;
        std::tie(weight, u, v) = edge;

        int x = find(parent, u);
        int y = find(parent, v);

        // If including this edge does not cause cycle, include it in the result and increment the index
        if (x != y) {
            result.push_back(std::make_tuple(u, v, weight));
            Union(parent, x, y);
            ++edgeCount;
        }
    }

    // Print the MST
    std::cout << "Edges of MST using Kruskal's algorithm:" << std::endl;
    for (const auto& edge : result) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        std::cout << u << " - " << v << " : " << weight << std::endl;
    }

    delete[] parent;
}