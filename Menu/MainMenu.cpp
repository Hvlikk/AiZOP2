//
// Created by Miłosz on 25.05.2024.
//
#include "iostream"
#include "MainMenu.h"
#include "../Algorithms/MST/Kruskal/Util/KruskalMenu.h"
#include "../Algorithms/MST/Prim/Util/PrimMenu.h"
#include "../Algorithms/ShortestPath/Dijkstra/Util/DijkstraMenu.h"
#include "../Algorithms/ShortestPath/Ford-Bellman/Util/FordBellmanMenu.h"
using namespace std;

void MainMenu::showMenu(){
    PrimMenu primMenu;
    KruskalMenu kruskalMenu;
    DijkstraMenu dijkstraMenu;
    FordBellmanMenu fordBellmanMenu;
    while(true){
        int x;
        cout << "Wybierz algorytm:\n";
        cout << "1. Prima\n";
        cout << "2. Kruskala\n";
        cout << "3. Dijkstry\n";
        cout << "4. Forda-Bellmana\n";
        cout << "5. Wyjscie\n";
        cin >> x;
        switch (x) {
            case 1:
                primMenu.showMenu();
                break;
            case 2:
                kruskalMenu.showMenu();
                break;
            case 3:
                dijkstraMenu.showMenu();
                break;
            case 4:
                fordBellmanMenu.showMenu();
                break;
            case 5:
                exit(0);
        }

    }

}