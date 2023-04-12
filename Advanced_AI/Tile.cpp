#include "Tile.h"
#include "Assets.h"

Tile::Tile() :
	Actor(), sprite(nullptr), tileState(TileState::Default), isSelected(false)
{
	sprite = new SpriteComponent(this, Assets::getTexture("DefaultTile"));
}

void Tile::setTileState(TileState tileStateP)
{
	tileState = tileStateP;
	updateTexture();
}

void Tile::toggleSelect()
{
	isSelected = !isSelected;
	updateTexture();
}

void Tile::updateTexture()
{
	switch (tileState)
	{
	case Tile::TileState::Obstacle:
		sprite->setTexture(Assets::getTexture("ObstacleTile"));
		break;
	case Tile::TileState::Start:
		sprite->setTexture(Assets::getTexture("StartTile"));
		break;
	case Tile::TileState::End:
		sprite->setTexture(Assets::getTexture("EndTile"));
		break;
	case Tile::TileState::Research:
		sprite->setTexture(Assets::getTexture("ResearchTile"));
		break;
	case Tile::TileState::Dijkstra:
		sprite->setTexture(Assets::getTexture("DijkstraTile"));
		break;
	case Tile::TileState::Astar:
		sprite->setTexture(Assets::getTexture("AstarTile"));
		break;
	case Tile::TileState::Default:
	default:
		sprite->setTexture(Assets::getTexture("DefaultTile"));
		break;
	}
}
