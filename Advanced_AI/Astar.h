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
	Astar(vector<vector<int>>* originalP, vector<vector<int>>* graphP);
	void mostShortWay(int start, int target);

private:
	vector<vector<int>>* graph;
	vector<vector<int>>* original;
	vector<int> distance;
	vector<int> openList;
	vector<int> closedList;
	vector<int> predecessor;
	vector<int> restNodes; // closed
	vector<int> neighbours;
	vector<int> heuristique;

	int getDistance(int node1, int node2);
	void reconstructPath(int start, int target);
	void findNeightbours(int node);
	void initialize(vector<vector<int>>* mat, int deb);
};

