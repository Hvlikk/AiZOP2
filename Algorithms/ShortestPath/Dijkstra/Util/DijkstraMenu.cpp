//
// Created by Miłosz on 29.05.2024.
//

#include "DijkstraMenu.h"
#include "../Struct/GraphListDijkstra.h"
#include "../Struct/GraphMatrixDijkstra.h"
#include <iostream>
#include <cmath>
using namespace std;

void DijkstraMenu::showMenu() {
    GraphListDijkstra* graphList = nullptr;
    GraphMatrixDijkstra* graphMatrix = nullptr;
    int vertices = 0;
    double density = 0.0;
    int startVertex = 0;
    int endVertex = 0;

    while (true) {
        int x;
        cout << "Wybierz algorytm:\n";
        cout << "1. Wczytaj dane z pliku\n";
        cout << "2. Wygeneruj graf\n";
        cout << "3. Wyswietl graf listowo\n";
        cout << "4. Wyswietl graf macierzowo\n";
        cout << "5. Znajdz MST\n";
        cout << "6. Powrot do wyboru algorytmu\n";
        cin >> x;

        switch (x) {
            case 1:
                // Implement loading from file if required
                break;
            case 2: {
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> vertices;
                cout << "Podaj gestosc grafu (w procentach): ";
                cin >> density;
                if (graphList) delete graphList;
                if (graphMatrix) delete graphMatrix;
                graphList = new GraphListDijkstra(vertices);
                graphList->generateSpanningTree();
                graphList->generateAdditionalEdges(density);
                int maxEdges = (vertices * (vertices - 1)) / 2;
                int totalEdges = round((density / 100.0) * maxEdges);
                graphMatrix = new GraphMatrixDijkstra(vertices, totalEdges);
                graphMatrix->setEdges(graphList->getEdges());
                break;
            }
            case 3:
                if (graphList) {
                    graphList->printAdjacencyList();
                } else {
                    cout << "Graf nie zostal wygenerowany.\n";
                }
                break;
            case 4:
                if (graphMatrix) {
                    graphMatrix->printIncidenceMatrix();
                } else {
                    cout << "Graf nie zostal wygenerowany.\n";
                }
                break;
            case 5:
                if (graphList && graphMatrix) {
                    cout << "Podaj wierzch. start";
                    cin >> startVertex;
                    cout << "Podaj wierzch. konc";
                    cin >> endVertex;
                    cout << "MST dla reprezentacji listowej:\n";
                    graphList->dijkstra(startVertex, endVertex);

                    cout << "\nMST dla reprezentacji macierzowej:\n";
                    graphMatrix->dijkstra(startVertex,endVertex);
                } else {
                    cout << "Graf nie zostal wygenerowany.\n";
                }
                break;
            case 6:
                delete graphList;
                delete graphMatrix;
                return;
        }
    }
}