#include <iostream>
#include <vector>
#include "Dij.h"
#include "Astar.h"

using namespace std;

void neightbours(vector<vector<int>>* graph, vector<vector<int>>* trans, int x, int y)
{
    int cptx = -1;
    while (cptx < 2)
    {
        if (x + cptx >= 0 && x + cptx < graph->size())
        {
            int cpty = -1;
            while (cpty < 2)
            {
                if (y + cpty >= 0 && y + cpty < graph->at(0).size())
                {
                    if (x + cptx == x && y + cpty == y)
                    {
                        trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 0;
                        //cout << "trans->at(" << x * graph->at(0).size() + y << ").at(" << (x + cptx) * graph->at(0).size() + y + cpty << ") = 0;" << endl;
                    }
                    else
                    {
                        if (graph->at(x + cptx).at(y + cpty) != 0)
                        {
                            if (cptx != 0 && cpty != 0)
                            {
                                if ((cptx == -1 && cpty == -1 && ((graph->at(x + cptx + 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty + 1) == 1))) ||
                                    (cptx == -1 && cpty == 1 && ((graph->at(x + cptx + 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty - 1) == 1))) ||
                                    (cptx == 1 && cpty == -1 && ((graph->at(x + cptx - 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty + 1) == 1))) ||
                                    (cptx == 1 && cpty == 1 && ((graph->at(x + cptx - 1).at(y + cpty) == 1) || (graph->at(x + cptx).at(y + cpty - 1) == 1))))
                                {
                                    trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 14;
                                }
                                else
                                {
                                    trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 1000000;
                                }
                            }
                            else
                            {
                                trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 10;
                            }
                        }
                        else
                        {
                            trans->at(x * graph->at(0).size() + y).at((x + cptx) * graph->at(0).size() + y + cpty) = 1000000;
                        }
                    }
                }
                cpty++;
            }
        }
        cptx++;
    }
}

vector<vector<int>> translate(vector<vector<int>>* graph)
{
    int size = graph->size() * graph->at(0).size();
    vector<vector<int>> trans;
    for (size_t i = 0; i < size; i++)
    {
        vector<int> temp;
        for (size_t j = 0; j < size; j++)
        {
            temp.push_back(1000000);
        }
        trans.push_back(temp);
    }

    for (size_t i = 0; i < graph->size(); i++)
    {
        for (size_t j = 0; j < graph->at(i).size(); j++)
        {
            neightbours(graph, &trans, i, j);
        }
    }

    return trans;
}

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
        {1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };
    
    vector<vector<int>> translated = translate(&graph2);

    /*
    for (size_t i = 0; i < translated.size(); i++)
    {
        for (size_t j = 0; j < translated.at(i).size(); j++)
        {
            cout << translated.at(i).at(j) << ", ";
        }
        cout << endl;
    }
    cout << endl;
    */

    /*
    Dij* dij = new Dij(&graph, 0);
    dij->Dijkstra();
    dij->Destination(3);
    */
    Dij* dij = new Dij(&translated, 0);
    dij->Dijkstra();
    dij->Destination(19);

    cout << endl;

    Astar* ast = new Astar(&graph2, &translated);
    ast->mostShortWay(0, 19);
}