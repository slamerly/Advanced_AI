#pragma once
#include <vector>

using namespace std;

class Dij

{
public:
	Dij(vector<vector<int>>* graphP, int debP);
	~Dij();


	void setGraph(vector<vector<int>>* graphP);
	void setStartNode(int startNodeP);
	void Dijkstra();

private:
	vector<vector<int>>* graph;
	vector<vector<int>> distance;
	vector<int> restNodes;
	vector<int> predecesor;
	int startNode;

	void initialize(vector<vector<int>>* mat, int deb);
	int findMin(vector<int> mat);
	int currentLine = 0;
	void updateDistance(int sommet1, int sommet2);
};

