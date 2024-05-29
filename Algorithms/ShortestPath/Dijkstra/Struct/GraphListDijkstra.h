//
// Created by Miłosz on 29.05.2024.
//

#ifndef AIZOP2_GRAPHLISTDIJKSTRA_H
#define AIZOP2_GRAPHLISTDIJKSTRA_H

#include <iostream>
#include <vector>
#include <utility>

class GraphListDijkstra {
public:
    GraphListDijkstra(int vertices);
    void addEdge(int src, int dest, int weight);
    void generateSpanningTree();
    void generateAdditionalEdges(double density);
    void printAdjacencyList() const;
    std::vector<std::tuple<int, int, int>> getEdges() const;
    bool isEdgePresent(int u, int v) const;
    void dijkstra(int startVertex, int endVertex); // New method for Dijkstra's algorithm

private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
};


#endif //AIZOP2_GRAPHLISTDIJKSTRA_H
