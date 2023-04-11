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

    vector<vector<int>> graph2{
        {1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    




    Dij* dij = new Dij(&graph, 0);
    dij->Dijkstra();
    dij->Destination(3);
}

vector<vector<int>> translate(vector<vector<int>>* graph)
{
    vector<vector<int>> trans;
    for (size_t i = 0; i < graph->size(); i++)
    {
        vector<int> temp;
        for (size_t j = 0; j < graph->size(); j++)
        {
            temp.push_back(1000000);
        }
        trans.push_back(temp);
    }


}

void findNeightbours(vector<vector<int>>* graph, int x, int y)
{
    vector<int> neighbours;
    int cptx = -1;
    while (cptx < 2)
    {
        if (x + cptx >= 0 && x + cptx < graph->size())
        {
            int cpty = -1;
            while (cpty < 2)
            {
                if (y + cpty >= 0 && y + cpty < graph->size())
                {
                    if (x + cptx == x && y + cpty == y)
                    {
                        neighbours.push_back(0);
                    }
                    else
                    {
                        if (graph->at(x + cptx).at(y + cpty) != 0)
                        {
                            neighbours.push_back(10);
                        }
                        else
                            neighbours.push_back(1000000);
                    }
                }
                else
                    neighbours.push_back(1000000);

                cpty++;
            }
        }
        else
        {
            for (size_t i = 0; i < 3; i++)
            {
                neighbours.push_back(1000000);
            }
        }
        cptx++;
    }
}