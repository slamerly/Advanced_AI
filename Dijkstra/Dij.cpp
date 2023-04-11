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
            //cout << restNodes.size() << endl;
            for (size_t i = 0; i < restNodes.size(); i++)
            {
                updateDistance(node1, restNodes.at(i));
            }
        }
    }

    //result
    cout << "RESULT - Origin(" << startNode << ")" << endl;
    cout << "Predecesor:    Distance:" << endl;
    for (size_t i = 0; i < predecessor.size(); i++)
    {
        cout << i << ": " << predecessor.at(i) << "               " << distance.at(i) << endl;
    }
    cout << endl;
}

void Dij::Destination(int dest)
{
    cout << endl << "DESTINATION(" << dest << ")" << endl;
    cout << "Cost: " << distance.at(dest) << endl;

    cout << "Road: ";
    int cpt = dest;
    while ( cpt != startNode )
    {
        cout << predecessor.at(cpt);
        cpt = predecessor.at(cpt);
        if (cpt != startNode)
            cout << " <- ";
    }
}

void Dij::initialize(vector<vector<int>>* mat, int deb)
{
    vector<int> line;
    for (size_t i = 0; i < mat->size(); i++)
    {
        if (i == deb)
            distance.push_back(0);
        else
            distance.push_back(1000000);
        //cout << distance.at(i) << ", ";

        predecessor.push_back(i);
    }
    //cout << endl;
}

int Dij::findMin(vector<int> mat)
{
    int min = 1000000;
    int node = -1;
    for (size_t i = 0; i < mat.size(); i++)
    {
        if (distance[mat[i]] <= min)
        {
            min = distance[mat[i]];
            node = mat[i];
        }
    }
    //cout << "Find min : " << node << endl;
    return node;
}

void Dij::updateDistance(int node1, int node2)
{
    if (distance.at(node2) > distance.at(node1) + graph->at(node1).at(node1) + graph->at(node1).at(node2))
    {
        distance[node2] = distance.at(node1) + (graph->at(node1).at(node1) + graph->at(node1).at(node2));
        predecessor[node2] = node1;
        //cout << node2 << ": dist: " << distance.at(node2) << ", predecesor: " << predecesor.at(node2) << endl;
    }
}
