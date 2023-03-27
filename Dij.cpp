#include "Dij.h"
#include <iostream>

void Dij::setGraph(vector<vector<int>>* graphP)
{
    graph = graphP;
}

void Dij::Dijkstra(vector<vector<int>>* graph, int deb)
{
    startNode = deb;
    initialize(graph, deb);
    predecesor.push_back(deb);

    for (size_t i = 0; i < graph->size(); i++)
    {
        restNodes.push_back(i);
    }

    while (!restNodes.empty())
    {
        int node1 = findMin(predecesor[predecesor.size()-1], restNodes);
        auto iter = find(begin(restNodes), end(restNodes), node1);
        if (iter != end(restNodes))
        {
            iter_swap(iter, end(restNodes) - 1);
            restNodes.pop_back();
            for (size_t i = 0; i < graph->size(); i++)
            {
                updateDistance(node1, graph->at(node1).at(i));
            }
        }
    }


    //result
    cout << "Way : " << endl;
    for (size_t i = 0; i < predecesor.size(); i++)
    {
        cout << "    " << predecesor.at(i) << endl;
    }
    cout << endl;

    //distance
    for (size_t i = 0; i < distance.size(); i++)
    {
        cout << i << ": ";
        for (size_t j = 0; j < distance.at(i).size(); j++) 
        {
            cout << distance.at(i).at(j) << ", ";
        }
        cout << endl;
    }
}

void Dij::initialize(vector<vector<int>>* mat, int deb)
{
    for (size_t i = 0; i < mat->size(); i++)
    {
        for (size_t j = 0; j < mat->size(); j++)
        {
            if(i == j)
                distance.at(i).at(j) = 0;
            else
                distance.at(i).at(j) = -1;
        }
    }
}

int Dij::findMin(int origin, vector<int> mat)
{
    int min = 1000000;
    int node = -1;
    for (size_t i = 0; i < mat.size(); i++)
    {
        if (distance[origin][i] < min)
        {
            min = distance[origin][i];
            node = i;
        }
    }
    return node;
}

void Dij::updateDistance(int node1, int node2)
{
    if (node2 != -1)
    {
        if (distance.at(startNode).at(node2) > distance.at(startNode).at(node1) + distance.at(node1).at(node2))
        {
            distance.at(startNode).at(node2) = distance.at(startNode).at(node1) + distance.at(node1).at(node2);
            predecesor.at(node2) = node1;
        }
    }
}
