#include "Dij.h"
#include <iostream>

Dij::Dij(vector<vector<int>>* graphP, int debP)
{
    graph = graphP;
    startNode = debP;
}

Dij::~Dij()
{
}

void Dij::setGraph(vector<vector<int>>* graphP)
{
    graph = graphP;
}

void Dij::setStartNode(int startNodeP)
{
    startNode = startNodeP;
}

void Dij::Dijkstra()
{
    initialize(graph, startNode);

    for (size_t i = 0; i < graph->size(); i++)
    {
        restNodes.push_back(i);
    }

    while (!restNodes.empty())
    {
        int node1 = findMin(restNodes);
        if (node1 != -1)
        {
            auto iter = find(begin(restNodes), end(restNodes), node1);
            restNodes.erase(iter);
            /*
            for (size_t i = 0; i < restNodes.size(); i++)
            {
                cout << restNodes[i] << ", ";
            }
            cout << endl;
            */
            cout << restNodes.size() << endl;
            for (size_t i = 0; i < restNodes.size(); i++)
            {
                updateDistance(node1, restNodes.at(i));
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
    vector<int> line;
    for (size_t i = 0; i < mat->size(); i++)
    {
        for (size_t j = 0; j < mat->size(); j++)
        {
            if (i == deb && j == deb)
                line.push_back(0);
            else
                line.push_back(1000000);
            cout << line.at(j) << ", ";
        }
        distance.push_back(line);
        line.clear();
        cout << endl;

        predecesor.push_back(i);
    }
}

int Dij::findMin(vector<int> mat)
{
    int min = 1000000;
    int node = -1;
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < distance.size(); j++)
        {
            if (distance[j][mat[i]] <= min)
            {
                min = distance[j][mat[i]];
                node = mat[i];
            }
        }
    }
    cout << "Find min : " << node << endl;
    return node;
}

void Dij::updateDistance(int node1, int node2)
{
    
    if (distance.at(startNode).at(node2) > distance.at(startNode).at(node1) + graph->at(node1).at(node1) + graph->at(node1).at(node2))
    {
        distance[startNode][node2] = distance.at(startNode).at(node1) + (graph->at(node1).at(node1)+ graph->at(node1).at(node2));
        predecesor[node2] = node1;
        cout << node2 << ": dist: " << distance.at(startNode).at(node2) << ", predecesor: " << predecesor.at(node2) << endl;
    }
}
