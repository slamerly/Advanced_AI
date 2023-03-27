#include <iostream>
#include <vector>
#include "Dij.h"

using namespace std;

int main()
{
    vector<vector<int>> graph = 
        {{0, 2, -1, 12},
        {-1, 0, 10, 5},
        {-1, -1, 0, -1},
        {12, -1, 8, 0}};

    Dij* dij = new Dij();
    dij->Dijkstra(graph, 0);
}