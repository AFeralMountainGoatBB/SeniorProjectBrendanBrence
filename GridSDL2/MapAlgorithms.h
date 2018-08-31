#pragma once
#include "Tile.h"
#include "EncounterInstance.h"

class SightAlgorithm
{
public:
	void DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target );

	std::pair<bool, bool> raytrace(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);

	std::pair<bool,bool> CheckAll(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);
	std::pair<bool, bool> CheckTile(int x, int y, std::vector<std::vector<Tile>> & TileMap);

	std::pair<bool, bool> GetBlockedOrObstructed() { return m_BlockedOrObstructed; }

private:
	std::pair<bool, bool> m_BlockedOrObstructed = { false,false }; //first is blocked, true if los blocked, second is obstructed, true if obstructed shot

};