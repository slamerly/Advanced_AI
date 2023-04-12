#pragma once
#include <vector>
#include "Tile.h"

using namespace std;

class Dijkstra

{
public:
	Dijkstra(vector<vector<int>>* graphP);

	void setGraph(vector<vector<int>>* graphP);
	void setStartNode(int startNodeP);
	void Research(int debP);
	void Destination(int dest);

	// Grid
	void setTiles(vector<vector<Tile*>>* refTiles);
	void updateTile(int node);

private:
	vector<vector<int>>* graph;
	vector<int> distance;
	vector<int> restNodes;
	vector<int> predecessor;
	int startNode;
	vector<vector<Tile*>>* tiles = nullptr;

	void initialize(vector<vector<int>>* mat, int deb);
	int findMin(vector<int> mat);
	int currentLine = 0;
	void updateDistance(int sommet1, int sommet2);
};

