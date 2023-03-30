#include "Astar.h"

void Astar::mostShortWay(vector<vector<int>> graph, Node start, Node target)
{
	Node currentNode;
	while (!restNodes.empty())
	{
		if (currentNode.x == target.x && currentNode.y == target.y)
		{
			//reconstructPath();
			//break;
		}
		else
		{
			for (size_t i = 0; i < neighbours.size(); i++)
			{
				auto iter = find(begin(restNodes), end(restNodes), neighbours.at(i));
				if (iter != end(restNodes) && distance.at(i) > neighbours.at(i).cost)
				{

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

void Astar::findNeightbours(Node node)
{
	neighbours.clear();
	for (int i = 0; i < graph->at(node.x).size(); i++)
	{
		if (graph->at(node.x).at(i) != 0 && graph->at(node.x).at(i) < 1000000)
		{
			neighbours.push_back({ node.x, i, graph->at(node.x).at(i), 0 });
		}
	}
}
