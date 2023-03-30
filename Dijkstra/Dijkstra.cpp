#include <iostream>
#include <vector>
#include "Dij.h"

using namespace std;

int main()
{
    vector<vector<int>> graph { 
        {0, 2, 1000000, 12},
        {1000000, 0, 10, 5},
        {1000000, 1000000, 0, 1000000},
        {12, 1000000, 8, 0}
    };

    Dij* dij = new Dij(&graph, 0);
    dij->Dijkstra();
    dij->Destination(3);
}