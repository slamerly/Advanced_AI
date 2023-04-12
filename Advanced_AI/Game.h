#pragma once
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Dijkstra.h"

using std::vector;

class Game
{
//Begin singleton
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator = (const Game&) = delete;
	Game(const Game&&) = delete;
	Game& operator = (const Game&&) = delete;

private:
	//Game() = default;
	Game() : isRunning(true), isUpdatingActors(false){}

//End singleton

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }

	// Game specific
	int getScore() { return score; }
	bool getPartyIsEnd() { return partyIsEnd; }
	Dijkstra* getDij() { return dij; }

	void setScore(int scoreP);
	void endGame();

private:
	void processInput();
	void update(float dt);
	void render();

	// Game specific
	void newParty();
	void neightbours(vector<vector<int>>* graph, vector<vector<int>>* trans, int x, int y);
	vector<vector<int>> translate(vector<vector<int>>* graph);

	Window window {};
	Renderer renderer;
	bool isRunning { true };

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific
	Grid* grid;
	vector<vector<int>> translated;
	Dijkstra* dij;
	int score;
	bool partyIsEnd = false;
};

