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
	int start;
	vector<int> distance;
	vector<int> onpenList;
	vector<int> closedList;
	vector<int> predecessor;
	vector<int> restNodes; // closed
	vector<int> neighbours;
	vector<int> heuristique;

	int compareHeur(Node node1, Node node2);
	int getDistance(int node1, int node2);
	void reconstructPath(int target);
	void findNeightbours(int node);
	void initialize(vector<vector<int>>* mat, int deb);
};

