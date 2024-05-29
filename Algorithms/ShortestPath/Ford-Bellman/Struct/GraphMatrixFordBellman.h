//
// Created by Miłosz on 29.05.2024.
//

#ifndef AIZOP2_GRAPHMATRIXFORDBELLMAN_H
#define AIZOP2_GRAPHMATRIXFORDBELLMAN_H
#include <iostream>
#include <vector>
#include <tuple>

class GraphMatrixFordBellman {
public:
    GraphMatrixFordBellman(int vertices, int edges);
    void addEdge(int edgeIndex, int vertex1, int vertex2, int weight);
    void setEdges(const std::vector<std::tuple<int, int, int>>& edges);
    void printIncidenceMatrix() const;
    void fordBellman(int startVertex, int endVertex) const; // Change return type to void
    std::vector<std::tuple<int, int, int>> getEdges() const;

private:
    int V, E;
    std::vector<std::vector<int>> incidenceMatrix;
};

#endif //AIZOP2_GRAPHMATRIXFORDBELLMAN_H
