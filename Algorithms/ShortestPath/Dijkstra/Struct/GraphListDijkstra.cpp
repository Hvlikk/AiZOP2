// GraphListPrim.cpp
#include "GraphListDijkstra.h"
#include <vector>
#include <queue>
#include <functional>
#include <tuple>
#include <iostream>
#include <ctime>
#include <cmath>
#include <climits>
#include <algorithm>

// Constructor
GraphListDijkstra::GraphListDijkstra(int vertices) : V(vertices) {
    adjacencyList.resize(V);
    std::srand(std::time(0)); // Initialize random number generator
}

// Add edge to the graph
void GraphListDijkstra::addEdge(int src, int dest, int weight) {
    adjacencyList[src].emplace_back(dest, weight);
    // For shortest path and max flow, treat edges as directed
    // adjacencyList[dest].emplace_back(src, weight); // Uncomment for undirected graph
}

// Generate a simple spanning tree
void GraphListDijkstra::generateSpanningTree() {
    std::vector<bool> visited(V, false);
    visited[0] = true;
    for (int i = 1; i < V; ++i) {
        int weight = std::rand() % 10 + 1; // random weight between 1-10
        addEdge(0, i, weight);
    }
}

// Generate additional edges based on density
void GraphListDijkstra::generateAdditionalEdges(double density) {
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
void GraphListDijkstra::printAdjacencyList() const {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : adjacencyList[i]) {
            std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}

// Get all edges in the graph
std::vector<std::tuple<int, int, int>> GraphListDijkstra::getEdges() const {
    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < V; ++i) {
        for (const auto& neighbor : adjacencyList[i]) {
            edges.emplace_back(i, neighbor.first, neighbor.second);
        }
    }
    return edges;
}

// Check if an edge is present
bool GraphListDijkstra::isEdgePresent(int u, int v) const {
    for (const auto& neighbor : adjacencyList[u]) {
        if (neighbor.first == v) {
            return true;
        }
    }
    return false;
}

// Implementing Dijkstra's algorithm
void GraphListDijkstra::dijkstra(int startVertex, int endVertex) {
    std::vector<int> distances(V, INT_MAX);
    std::vector<int> previous(V, -1);
    distances[startVertex] = 0;

    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.emplace(0, startVertex);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distances[u]) continue;

        for (const auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.emplace(distances[v], v);
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
        for (const auto& neighbor : adjacencyList[u]) {
            if (neighbor.first == v) {
                weight = neighbor.second;
                break;
            }
        }
        std::cout << "(" << u << " -> " << v << ", weight: " << weight << ") ";
    }
    std::cout << std::endl;
}