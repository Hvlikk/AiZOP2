#ifndef GRAPH_LIST_PRIM_H
#define GRAPH_LIST_PRIM_H

#include <iostream>
#include <vector>
#include <utility>

class GraphListPrim {
public:
    GraphListPrim(int vertices);
    void addEdge(int src, int dest, int weight);
    void generateSpanningTree();
    void generateAdditionalEdges(double density);
    void printAdjacencyList() const;
    void primMST() const;
    std::vector<std::tuple<int, int, int>> getEdges() const;

private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
    void dfs(int v, std::vector<bool>& visited);
    bool isEdgePresent(int u, int v) const;
};

#endif // GRAPH_LIST_PRIM_H