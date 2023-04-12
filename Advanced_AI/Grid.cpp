#include "Grid.h"
#include "Tile.h"
#include <iostream>

Grid::Grid() :
	Actor(), selectedTile(nullptr)
{
	tiles.resize(NB_ROWS);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(NB_COLS);
	}
	// Create tiles
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			tiles[i][j] = new Tile();
			tiles[i][j]->setPosition(Vector2(TILESIZE / 2.0f + j * TILESIZE, START_Y + i * TILESIZE));

			if( rand() % 2 == 0)
				tiles[i][j]->setTileState(Tile::TileState::Default);
			else
				tiles[i][j]->setTileState(Tile::TileState::Obstacle);
		}
	}

	// Set start/end tiles
	//getStartTile().setTileState(Tile::TileState::Default);
	//getEndTile().setTileState(Tile::TileState::Border);
}

Grid::Grid(std::vector<std::vector<int>>* circuit) :
	Actor(), selectedTile(nullptr)
{
	tiles.resize(NB_ROWS);
	for (size_t i = 0; i < tiles.size(); i++)
	{
		tiles[i].resize(NB_COLS);
	}
	// Create tiles
	for (size_t i = 0; i < NB_ROWS; i++)
	{
		for (size_t j = 0; j < NB_COLS; j++)
		{
			tiles[i][j] = new Tile();
			tiles[i][j]->setPosition(Vector2(TILESIZE / 2.0f + j * TILESIZE, START_Y + i * TILESIZE));
			tiles[i][j]->setTileState(Tile::TileState::Default);

			/*
			switch (circuit->at(i).at(j))
			{
			case 0:
			default:
				tiles[i][j]->setTileState(Tile::TileState::Default);
				break;
			case 1:
				tiles[i][j]->setTileState(Tile::TileState::Border);
				break;
			case 2:
				tiles[i][j]->setTileState(Tile::TileState::Tree);
				break;
			case 3:
				tiles[i][j]->setTileState(Tile::TileState::Building);
				break;
			}
			*/
		}
	}
}

void Grid::processClick(int x, int y)
{
	
	y -= static_cast<int>(START_Y - TILESIZE / 2);
	if (y >= 0)
	{
		std::cout << "hemm" << std::endl;
		x /= static_cast<int>(TILESIZE);
		y /= static_cast<int>(TILESIZE);

		if (x >= 0 && x < static_cast<int>(NB_COLS) && y >= 0 && y < static_cast<int>(NB_ROWS))
		{
			selectTile(y, x);
		}
	}
}

Tile& Grid::getStartTile()
{
	return *tiles[3][0];
}

Tile& Grid::getEndTile()
{
	return *tiles[3][NB_COLS-1];
}

void Grid::selectTile(size_t row, size_t col)
{
	// Make sure it's a valid selection
	Tile::TileState state = tiles[row][col]->getTileState();
	if (state != Tile::TileState::Obstacle)
	{
		// Deselect previous one
		if (selectedTile)
		{
			selectedTile->toggleSelect();
		}
		selectedTile = tiles[row][col];

		if (!containStart)
		{
			selectedTile->setTileState(Tile::TileState::Start);
			selectedTile->toggleSelect();
			return;
		}

		if (!containEnd)
		{
			selectedTile->setTileState(Tile::TileState::End);
			selectedTile->toggleSelect();
			return;
		}
	}
}
