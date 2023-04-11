#include "Astar.h"
#include <iostream>
#include <math.h>

Astar::Astar(vector<vector<int>>* originalP, vector<vector<int>>* graphP)
{
	original = originalP;
	graph = graphP;
}

void Astar::mostShortWay(int startP, int target)
{
	/*
	int currentNode;
	initialize(graph, start);

	auto iter = find(begin(restNodes), end(restNodes), start);
	restNodes.erase(iter);


	while (!restNodes.empty())
	{
		currentNode = restNodes.at(0);
		if (currentNode == target)
		{
			std::cout << "end" << std::endl;
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
	*/

	//predecessor.push_back(start);
	start = startP;

	int currentNode;
	initialize(graph, start);

	while (!onpenList.empty())
	{
		currentNode = onpenList.at(0);
		//std::cout << currentNode << " - ";
		for (size_t i = 0; i < onpenList.size(); i++)
		{
			//if (onpenList.at(i) < distance.at(currentNode))
			if (distance.at(i) < distance.at(currentNode) || (distance.at(i) == distance.at(currentNode) && heuristique.at(i) < heuristique.at(currentNode)))
				currentNode = onpenList.at(i);
		}
		//std::cout << currentNode << std::endl;

		auto iter = find(begin(onpenList), end(onpenList), currentNode);
		onpenList.erase(iter);
		closedList.push_back(currentNode);

		if (currentNode == target)
		{
			reconstructPath(target);
			//break;
			return;
		}

		findNeightbours(currentNode);

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			auto neightClosedList = find(begin(closedList), end(closedList), neighbours.at(i));
			auto neightOpenList = find(begin(onpenList), end(onpenList), neighbours.at(i));

			//int graphx = neighbours.at(i) / graph->at(0).size();
			//int graphy = (neighbours.at(i) % graph->at(0).size()) - 1;

			//cout << neighbours.at(i) << ": " << graphx << ", " << graphy << endl;

			cout << neighbours.at(i) << ": " << endl;
			int newDistance = distance.at(currentNode) + getDistance(currentNode, neighbours.at(i));

			//if (!(neightClosedList != end(closedList) || ((neightOpenList != end(onpenList)) && (distance.at(neighbours.at(i)) < graph->at(currentNode).at(neighbours.at(i))))))
			if (!(neightClosedList != end(closedList) || ((neightOpenList != end(onpenList)) && (distance.at(neighbours.at(i)) < newDistance))))
			{
				cout << "distance: " << newDistance << endl;
				//distance.at(neighbours.at(i)) = distance.at(currentNode) + graph->at(currentNode).at(neighbours.at(i));
				distance.at(neighbours.at(i)) = newDistance;
				heuristique.at(neighbours.at(i)) = getDistance(neighbours.at(i), target);
				predecessor.at(neighbours.at(i)) = currentNode;

				if (neightOpenList == end(onpenList))
				{
					onpenList.push_back(neighbours.at(i));
				}
			}
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

int Astar::getDistance(int node1, int node2)
{
	int node1x = node1 / original->size();
	int node1y = node1 % original->at(0).size() - 1;
	int node2x = node2 / original->size();
	int node2y = node2 % original->at(0).size() - 1;
	int dstX = abs(node1x - node2x);
	int dstY = abs(node1y - node2y);

	cout << dstX << ", " << dstY << endl;

	if (dstX > dstY)
		return 14 * dstY + 10 * (dstX - dstY);
	return 14 * dstX + 10 * (dstY - dstX);
}

void Astar::reconstructPath(int target)
{
	cout << "ORIGIN(" << start << ") - DESTINATION(" << target << ")" << endl;
	cout << "Cost: " << distance.at(target) << endl;

	cout << "Road: " << target << " <- ";
	int cpt = target;
	while (cpt != start)
	{
		cout << predecessor.at(cpt);
		cpt = predecessor.at(cpt);
		if (cpt != start)
			cout << " <- ";
	}
}

void Astar::findNeightbours(int node)
{
	neighbours.clear();
	for (int i = 0; i < graph->at(node).size(); i++)
	{
		if (graph->at(node).at(i) != 0 && graph->at(node).at(i) < 1000000)
		{
			//std::cout << i << ", ";
			neighbours.push_back(i);
		}
	}
	//std::cout << std::endl;
}

void Astar::initialize(vector<vector<int>>* mat, int deb)
{
	onpenList.push_back(deb);

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
		//restNodes.push_back(i);
	}
}
