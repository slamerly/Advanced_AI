#pragma once
#include <vector>

using namespace std;

struct Node
{
	int x, y, cost, heur; // heur: heuristique
};

class Astar
{
public:
	void mostShortWay(vector<vector<int>> graph, Node start, Node end);

private:
	vector<vector<int>>* graph;
	Node start;
	vector<int> distance;
	vector<int> predecessor;
	vector<int> restNodes;
	vector<Node> neighbours;

	int compareHeur(Node node1, Node node2);
	void reconstructPath();
	void findNeightbours(Node node);
};

