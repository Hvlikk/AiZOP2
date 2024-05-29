//
// Created by Miłosz on 29.05.2024.
//

#ifndef AIZOP2_GRAPHLISTFORDBELLMAN_H
#define AIZOP2_GRAPHLISTFORDBELLMAN_H

#include <iostream>
#include <vector>
#include <tuple>

class GraphListFordBellman {
public:
    GraphListFordBellman(int vertices);
    void addEdge(int src, int dest, int weight);
    void generateSpanningTree();
    void generateAdditionalEdges(double density);
    void printAdjacencyList() const;
    std::vector<std::tuple<int, int, int>> getEdges() const;
    bool isEdgePresent(int u, int v) const;
    void fordBellman(int startVertex, int endVertex); // New method for Dijkstra's algorithm

private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
};


#endif //AIZOP2_GRAPHLISTFORDBELLMAN_H
