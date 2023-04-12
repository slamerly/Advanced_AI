#pragma once
#include <vector>

using namespace std;

class Dijkstra

{
public:
	Dijkstra(vector<vector<int>>* graphP, int debP);
	~Dijkstra();

	void setGraph(vector<vector<int>>* graphP);
	void setStartNode(int startNodeP);
	void Research();
	void Destination(int dest);

private:
	vector<vector<int>>* graph;
	vector<int> distance;
	vector<int> restNodes;
	vector<int> predecessor;
	int startNode;

	void initialize(vector<vector<int>>* mat, int deb);
	int findMin(vector<int> mat);
	int currentLine = 0;
	void updateDistance(int sommet1, int sommet2);
};

