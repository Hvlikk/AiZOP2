#ifndef GRAPH_LIST_KRUSKAL_H
#define GRAPH_LIST_KRUSKAL_H

#include <iostream>
#include <vector>
#include <utility>

class GraphListKruskal {
public:
    GraphListKruskal(int vertices);
    void addEdge(int src, int dest, int weight);
    void generateSpanningTree();
    void generateAdditionalEdges(double density);
    void printAdjacencyList() const;
    void kruskalMST() const;
    std::vector<std::tuple<int, int, int>> getEdges() const;
    int findParent(std::vector<int>& parent, int vertex) const;
    void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v) const;
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adjacencyList;
    void dfs(int v, std::vector<bool>& visited);
    bool isEdgePresent(int u, int v) const;
};

#endif // GRAPH_LIST_KRUSKAL_H