#include "GraphMatrixKruskal.h"
#include <vector>
#include <tuple>
#include <algorithm> // for std::sort
#include <numeric>   // for std::iota
#include <iostream>


// Union-Find data structure to keep track of connected components
class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
            return true;
        }
        return false;
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};


GraphMatrixKruskal::GraphMatrixKruskal(int vertices, int edges) : V(vertices), E(edges) {
    incidenceMatrix.resize(V, std::vector<int>(E * 2, 0)); // Allocate twice the number of edges
}

// Add edge to the graph
void GraphMatrixKruskal::addEdge(int edgeIndex, int vertex1, int vertex2, int weight) {
    incidenceMatrix[vertex1][edgeIndex] = weight;
    incidenceMatrix[vertex2][edgeIndex] = weight;

    // Also add the edge in the reverse direction for undirected graph
    incidenceMatrix[vertex1][edgeIndex + 1] = weight;
    incidenceMatrix[vertex2][edgeIndex + 1] = weight;
}

// Set multiple edges in the graph
void GraphMatrixKruskal::setEdges(const std::vector<std::tuple<int, int, int>>& edges) {
    int edgeIndex = 0;
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        addEdge(edgeIndex++, u, v, weight);
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


// Prim's algorithm to generate the MST
void GraphMatrixKruskal::kruskalMST() const {
    // Step 1: Extract edges and their weights
    std::vector<std::tuple<int, int, int>> edges; // (weight, vertex1, vertex2)
    for (int i = 0; i < E * 2; i += 2) {
        for (int u = 0; u < V; ++u) {
            if (incidenceMatrix[u][i] != 0) {
                for (int v = u + 1; v < V; ++v) {
                    if (incidenceMatrix[v][i] == incidenceMatrix[u][i]) {
                        edges.emplace_back(incidenceMatrix[u][i], u, v);
                        break;
                    }
                }
            }
        }
    }

    // Step 2: Sort edges by weight
    std::sort(edges.begin(), edges.end());

    // Step 3: Use Union-Find to select edges for the MST
    UnionFind uf(V);
    std::vector<std::tuple<int, int, int>> mstEdges;
    int mstWeight = 0;

    for (const auto& edge : edges) {
        int weight, u, v;
        std::tie(weight, u, v) = edge;
        if (uf.unionSets(u, v)) {
            mstEdges.push_back(edge);
            mstWeight += weight;
        }
    }

    // Print the MST
    std::cout << "Edges in the MST:" << std::endl;
    for (const auto& edge : mstEdges) {
        int weight, u, v;
        std::tie(weight, u, v) = edge;
        std::cout << u << " - " << v << " (Weight: " << weight << ")" << std::endl;
    }
    std::cout << "Total weight of MST: " << mstWeight << std::endl;
}