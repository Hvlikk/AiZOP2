// GraphMatrixPrim.h
#ifndef GRAPH_MATRIX_PRIM_H
#define GRAPH_MATRIX_PRIM_H

#include <iostream>
#include <vector>
#include <tuple>

class GraphMatrixPrim {
public:
    GraphMatrixPrim(int vertices, int edges);
    void addEdge(int edgeIndex, int vertex1, int vertex2, int weight);
    void setEdges(const std::vector<std::tuple<int, int, int>>& edges);
    void printIncidenceMatrix() const;
    void primMST() const; // Change return type to void

private:
    int V, E;
    std::vector<std::vector<int>> incidenceMatrix;
};

#endif // GRAPH_MATRIX_PRIM_H