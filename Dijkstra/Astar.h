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
	void mostShortWay(vector<vector<int>>* graph, int start, int end);

private:
	vector<vector<int>>* graph;
	int start;
	vector<int> distance;
	vector<int> predecessor;
	vector<int> restNodes;
	vector<int> neighbours;

	int compareHeur(Node node1, Node node2);
	void reconstructPath();
	void findNeightbours(int node);
	void initialize(vector<vector<int>>* mat, int deb);
};

