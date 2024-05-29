//
// Created by Miłosz on 29.05.2024.
//

#include "GraphMatrixFordBellman.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <queue>
#include <climits>


GraphMatrixFordBellman::GraphMatrixFordBellman(int vertices, int edges) : V(vertices), E(edges) {
    incidenceMatrix.resize(V, std::vector<int>(E, 0)); // Allocate twice the number of edges
}

// Add edge to the graph
void GraphMatrixFordBellman::addEdge(int edgeIndex, int vertex1, int vertex2, int weight) {
    incidenceMatrix[vertex1][edgeIndex] = weight;
    incidenceMatrix[vertex2][edgeIndex] = weight;
}

// Set multiple edges in the graph
void GraphMatrixFordBellman::setEdges(const std::vector<std::tuple<int, int, int>>& edges) {
    int edgeIndex = 0;
    for (const auto& edge : edges) {
        int u, v, weight;
        std::tie(u, v, weight) = edge;
        addEdge(edgeIndex, u, v, weight);
        edgeIndex++;
    }
}

// Print the incidence matrix
void GraphMatrixFordBellman::printIncidenceMatrix() const {
    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}


// Prim's algorithm to generate the MST
void GraphMatrixFordBellman::fordBellman(int startVertex, int endVertex) const {
    std::vector<int> distances(V, INT_MAX);
    std::vector<int> previous(V, -1);
    distances[startVertex] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < V - 1; ++i) {
        for (int edgeIndex = 0; edgeIndex < E; ++edgeIndex) {
            for (int u = 0; u < V; ++u) {
                if (incidenceMatrix[u][edgeIndex] != 0) {
                    int v = -1;
                    for (int w = 0; w < V; ++w) {
                        if (incidenceMatrix[w][edgeIndex] == -incidenceMatrix[u][edgeIndex]) {
                            v = w;
                            break;
                        }
                    }
                    if (v != -1 && distances[u] != INT_MAX && distances[u] + incidenceMatrix[u][edgeIndex] < distances[v]) {
                        distances[v] = distances[u] + incidenceMatrix[u][edgeIndex];
                        previous[v] = u;
                    }
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int edgeIndex = 0; edgeIndex < E; ++edgeIndex) {
        for (int u = 0; u < V; ++u) {
            if (incidenceMatrix[u][edgeIndex] != 0) {
                int v = -1;
                for (int w = 0; w < V; ++w) {
                    if (incidenceMatrix[w][edgeIndex] == -incidenceMatrix[u][edgeIndex]) {
                        v = w;
                        break;
                    }
                }
                if (v != -1 && distances[u] != INT_MAX && distances[u] + incidenceMatrix[u][edgeIndex] < distances[v]) {
                    std::cout << "Graph contains a negative-weight cycle" << std::endl;
                    return;
                }
            }
        }
    }

    // Output the shortest path
    if (distances[endVertex] == INT_MAX) {
        std::cout << "No path exists from " << startVertex << " to " << endVertex << std::endl;
        return;
    }

    std::vector<int> path;
    for (int at = endVertex; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest path from " << startVertex << " to " << endVertex << ": ";
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\nTotal cost: " << distances[endVertex] << std::endl;

    // Print edges and their weights
    std::cout << "Edges and their weights: ";
    for (int i = 0; i < path.size() - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];
        int weight = 0;
        for (int edgeIndex = 0; edgeIndex < E; ++edgeIndex) {
            if ((incidenceMatrix[u][edgeIndex] > 0 && incidenceMatrix[v][edgeIndex] < 0) ||
                (incidenceMatrix[u][edgeIndex] < 0 && incidenceMatrix[v][edgeIndex] > 0)) {
                weight = std::abs(incidenceMatrix[u][edgeIndex]);
                break;
            }
        }
        std::cout << "(" << u << " -> " << v << ", weight: " << weight << ") ";
    }
    std::cout << std::endl;
}