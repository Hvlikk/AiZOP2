cmake_minimum_required(VERSION 3.28)
project(aizop2)

set(CMAKE_CXX_STANDARD 17)

add_executable(aizop2 Menu/main.cpp
        Menu/MainMenu.cpp
        Menu/MainMenu.h
        Algorithms/MST/Prim/Util/PrimMenu.cpp
        Algorithms/MST/Prim/Util/PrimMenu.h
        Algorithms/MST/Prim/Struct/GraphListPrim.cpp
        Algorithms/MST/Prim/Struct/GraphListPrim.h
        Algorithms/MST/Prim/Struct/GraphMatrixPrim.cpp
        Algorithms/MST/Prim/Struct/GraphMatrixPrim.h
        Algorithms/MST/Kruskal/Util/KruskalMenu.cpp
        Algorithms/MST/Kruskal/Util/KruskalMenu.h
        Algorithms/MST/Kruskal/Struct/GraphListKruskal.cpp
        Algorithms/MST/Kruskal/Struct/GraphListKruskal.h
        Algorithms/MST/Kruskal/Struct/GraphMatrixKruskal.cpp
        Algorithms/MST/Kruskal/Struct/GraphMatrixKruskal.h
        Algorithms/ShortestPath/Dijkstra/Util/DijkstraMenu.cpp
        Algorithms/ShortestPath/Dijkstra/Util/DijkstraMenu.h
        Algorithms/ShortestPath/Dijkstra/Struct/GraphListDijkstra.cpp
        Algorithms/ShortestPath/Dijkstra/Struct/GraphListDijkstra.h
        Algorithms/ShortestPath/Dijkstra/Struct/GraphMatrixDijkstra.cpp
        Algorithms/ShortestPath/Dijkstra/Struct/GraphMatrixDijkstra.h
        Algorithms/ShortestPath/Ford-Bellman/Util/FordBellmanMenu.cpp
        Algorithms/ShortestPath/Ford-Bellman/Util/FordBellmanMenu.h
        Algorithms/ShortestPath/Ford-Bellman/Struct/GraphListFordBellman.cpp
        Algorithms/ShortestPath/Ford-Bellman/Struct/GraphListFordBellman.h
        Algorithms/ShortestPath/Ford-Bellman/Struct/GraphMatrixFordBellman.cpp
        Algorithms/ShortestPath/Ford-Bellman/Struct/GraphMatrixFordBellman.h)
