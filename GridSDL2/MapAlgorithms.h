#pragma once
#include "Tile.h"
#include "EncounterInstance.h"

class SightAlgorithm
{
public:
	void DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target );

	std::pair<int, int> PixelToGrid(std::vector<std::vector<Tile>>&TileMap, std::pair<int, int> Source);
	void GeneratePairs(std::pair<int, int> Source, std::pair<int, int> Target);
	std::pair<double, double> FindTopLeft(std::pair<int, int> Source);
	std::pair<double, double> FindTopRight(std::pair<int, int> Source);
	std::pair<double, double> FindBottomLeft(std::pair<int, int> Source);
	std::pair<double, double> FindBottomRight(std::pair<int, int> Source);
	std::pair<bool, bool> raytrace(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);
	
	float FindSlope(std::pair<int, int> Source, std::pair<int, int> Target);

	std::pair<bool,bool> CheckAll(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap);
	std::pair<bool, bool> CheckTile(int x, int y, std::vector<std::vector<Tile>> & TileMap);

private:
	std::vector< std::pair< std::pair<double, double>, std::pair<double, double>>> PairsToCheck;
	std::pair<bool, bool> BlockedOrObstructed = { false,false };
	std::pair<bool, bool> TopLeft = { true, false };
	std::pair<bool, bool> TopRight = { true , false };
	std::pair<bool, bool> BottomLeft = { true , false };
	std::pair<bool, bool> BottomRight = { true , false };

};