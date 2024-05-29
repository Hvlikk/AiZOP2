// GraphMatrixPrim.h
#ifndef GRAPH_MATRIX_KRUSKAL_H
#define GRAPH_MATRIX_KRUSKAL_H

#include <iostream>
#include <vector>
#include <tuple>

class GraphMatrixKruskal {
public:
    GraphMatrixKruskal(int vertices, int edges);
    void addEdge(int edgeIndex, int vertex1, int vertex2, int weight);
    void setEdges(const std::vector<std::tuple<int, int, int>>& edges);
    void printIncidenceMatrix() const;
    void kruskalMST() const; // Change return type to void
    int find(int parent[], int i) const;
    void Union(int parent[], int x, int y) const;
    std::vector<std::tuple<int, int, int>> getEdges() const;

private:
    int V, E;
    std::vector<std::vector<int>> incidenceMatrix;
};

#endif // GRAPH_MATRIX_KRUSKAL_H