#pragma once
#include "Actor.h"

class Grid :
    public Actor
{
public:
    Grid();
    Grid(std::vector<std::vector<int>>* circuit);

    void processClick(int x, int y);
    class Tile& getStartTile();
    class Tile& getEndTile();

    std::vector<std::vector<class Tile*>>* getTiles() { return &tiles; }

private:
    void selectTile(size_t row, size_t col);
    class Tile* selectedTile;

    bool containStart = false;
    bool containEnd = false;

    int posStart;
    int posEnd;

    // 2D vector of tiles in grid
    std::vector<std::vector<class Tile*>> tiles;

    const size_t NB_ROWS = 15*2;
    const size_t NB_COLS = 20*2; // 16

    // Start y position of top left corner
    const float START_Y = 20/2;

    const float TILESIZE = 40.0f/2;
};

