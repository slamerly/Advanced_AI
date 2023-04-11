#include "Astar.h"

void Astar::mostShortWay(vector<vector<int>>* graph, int start, int target)
{
	int currentNode;
	initialize(graph, start);

	auto iter = find(begin(restNodes), end(restNodes), start);
	restNodes.erase(iter);


	while (!restNodes.empty())
	{
		currentNode = restNodes.at(0);
		if (currentNode == target)
		{
			//reconstructPath();
			//break;
		}
		else
		{
			findNeightbours(currentNode);
			for (size_t i = 0; i < neighbours.size(); i++)
			{
				auto iter = find(begin(restNodes), end(restNodes), restNodes.at(i));
				if (iter != end(restNodes) && distance.at(neighbours.at(i)) > graph->at(currentNode).at(neighbours.at(i)))
				{
					distance.at(neighbours.at(i)) = distance.at(currentNode) + graph->at(currentNode).at(neighbours.at(i));
					heuristique.at(neighbours.at(i)) = distance.at(neighbours.at(i)) + (int(target / graph->size()) - int(currentNode / graph->size())) + (target % graph->size() - neighbours.at(i));
				}
			}
			//auto iter = find(begin(restNodes), end(restNodes), node1);
		}
	}
}

int Astar::compareHeur(Node node1, Node node2)
{
	if (node1.heur < node2.heur)
		return 1;
	else if (node1.heur == node2.heur)
		return 0;
	else
		return -1;
}

void Astar::reconstructPath()
{
}

void Astar::findNeightbours(int node)
{
	neighbours.clear();
	for (int i = 0; i < graph->at(node).size(); i++)
	{
		if (graph->at(node).at(i) != 0 && graph->at(node).at(i) < 1000000)
		{
			neighbours.push_back(i);
		}
	}
}

void Astar::initialize(vector<vector<int>>* mat, int deb)
{
	vector<int> line;
	for (size_t i = 0; i < mat->size(); i++)
	{
		if (i == deb)
		{
			distance.push_back(0);
			heuristique.push_back(0);
		}
		else
		{
			distance.push_back(1000000);
			heuristique.push_back(1000000);
		}

		predecessor.push_back(i);
		restNodes.push_back(i);
	}
}
