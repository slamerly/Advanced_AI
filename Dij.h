#pragma once
#include <vector>

using namespace std;

class Dij

{
public:
	void setGraph(vector<vector<int>>* graphP);
	void Dijkstra(vector<vector<int>>* graph, int deb);

private:
	vector<vector<int>>* graph;
	vector<vector<int>> distance;
	vector<int> restNodes;
	vector<int> predecesor;
	int startNode;

	void initialize(vector<vector<int>>* mat, int deb);
	int findMin(int origin, vector<int> mat);
	void updateDistance(int sommet1, int sommet2);
};

