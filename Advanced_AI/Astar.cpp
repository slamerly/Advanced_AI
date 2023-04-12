#include "Astar.h"
#include <iostream>
#include <math.h>

Astar::Astar(vector<vector<int>>* originalP, vector<vector<int>>* graphP)
{
	original = originalP;
	graph = graphP;
}

void Astar::mostShortWay(int start, int target)
{
	int currentNode;
	initialize(graph, start);

	while (!openList.empty())
	{
		currentNode = openList.at(0);
		//cout << "currentNode : " << currentNode << endl;

		for (size_t i = 1; i < openList.size(); i++)
		{
			if (distance.at(openList.at(i)) < distance.at(currentNode) || (distance.at(openList.at(i)) == distance.at(currentNode) && heuristique.at(openList.at(i)) < heuristique.at(currentNode)))
			{
				currentNode = openList.at(i);
				//cout << "currentNode : " << currentNode << endl;
			}
		}

		auto iter = find(begin(openList), end(openList), currentNode);
		openList.erase(iter);
		closedList.push_back(currentNode);

		if (currentNode == target)
		{
			reconstructPath(start, target);
			return;
		}

		findNeightbours(currentNode);

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			//cout << neighbours.at(i) << " - ";
			auto neightClosedList = find(begin(closedList), end(closedList), neighbours.at(i));
			auto neightOpenList = find(begin(openList), end(openList), neighbours.at(i));

			int newDistance = distance.at(currentNode) + getDistance(currentNode, neighbours.at(i));

			if (!(neightClosedList != end(closedList)) && (!(neightOpenList != end(openList)) || (newDistance < distance.at(neighbours.at(i)))))
			{
				//cout << neighbours.at(i) << " - ";
				//cout << newDistance << endl;
				distance.at(neighbours.at(i)) = newDistance;
				heuristique.at(neighbours.at(i)) = getDistance(neighbours.at(i), target);
				predecessor.at(neighbours.at(i)) = currentNode;

				if (neightOpenList == end(openList))
				{
					openList.push_back(neighbours.at(i));
				}
			}
		}
	}

}

int Astar::getDistance(int node1, int node2)
{
	int node1x = node1 / original->size();
	int node1y = node1 % original->at(0).size() - 1;
	int node2x = node2 / original->size();
	int node2y = node2 % original->at(0).size() - 1;
	int dstX = abs(node1x - node2x);
	int dstY = abs(node1y - node2y);

	if (dstX > dstY)
		return 14 * dstY + 10 * (dstX - dstY);
	return 14 * dstX + 10 * (dstY - dstX);
}

void Astar::reconstructPath(int start, int target)
{
	cout << "---- ASTAR ----" << endl;
	cout << "ORIGIN(" << start << ") - DESTINATION(" << target << ")" << endl;
	cout << "Cost: " << distance.at(target) << endl;

	cout << "Road: " << target << " <- ";
	int node = target;
	while (node != start)
	{
		cout << predecessor.at(node);
		node = predecessor.at(node);
		if (node != start)
			cout << " <- ";
	}
}

void Astar::findNeightbours(int node)
{
	//cout << node << ": " << endl;
	neighbours.clear();
	for (int i = 0; i < graph->at(node).size(); i++)
	{
		if (graph->at(node).at(i) != 0 && graph->at(node).at(i) < 1000000)
		{
			//cout << i << ", ";
			neighbours.push_back(i);
		}
	}
	//cout << endl;
}

void Astar::initialize(vector<vector<int>>* mat, int deb)
{
	openList.push_back(deb);

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
	}
}
