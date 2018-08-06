#include "MapAlgorithms.h"


void SightAlgorithm::DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target)
{
	BlockedOrObstructed = raytrace(std::make_pair(Source.first, Source.second), std::make_pair(Target.first, Target.second), TileMap);
}

std::pair<bool, bool> SightAlgorithm::raytrace(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap)
{
	std::pair<bool, bool> BlockedObstructed;
	std::pair<bool, bool> TempBool;
		int dx = abs(Target.first - Source.first);
		int dy = abs(Target.second - Source.second);
		int x = Source.first;
		int y = Source.second;
		int n = 1 + dx + dy;
		int x_inc = (Target.first > Source.first) ? 1 : -1;
		int y_inc = (Target.second > Source.second) ? 1 : -1;
		int error = dx - dy;
		dx *= 2;
		dy *= 2;

		for (; n > 0; --n)
		{
			//this statement checks to see if we are looking at the start or end tiles, two tiles that should not be checked for obstructions or blocking
			if (((x == Source.first && y == Source.second) || (x == Target.first && y == Target.second))==false)
			{
				std::cout << "x:" << x << " y:" << y << std::endl;
				TempBool = CheckTile(x, y, TileMap);
			}
			if (TempBool.first == true)
			{
				BlockedObstructed.first = true;
				BlockedObstructed.second = true;
				return BlockedObstructed;
			}
			else if (TempBool.second == true)
			{
				BlockedObstructed.second = true;
			}
			
			if (error > 0)
			{
				x += x_inc;
				error -= dy;
			}
			else
			{
				y += y_inc;
				error += dx;
			}
	}
	return BlockedObstructed;
}

std::pair<bool, bool> SightAlgorithm:: CheckTile(int x, int y, std::vector<std::vector<Tile>> & TileMap)
{
	bool block;
	bool obstructed;
	if (TileMap[x][y].getType()>TILE_STONE && TileMap[x][y].getType()!=TILE_WATER)
	{
		block = true;
	}
	if (TileMap[x][y].EntityPresent())
	{
		obstructed = true;
	}
	return (std::make_pair(block, obstructed));
}

std::pair<bool,bool> SightAlgorithm::CheckAll(std::pair<int, int> Source, std::pair<int, int> Target, std::vector<std::vector<Tile>> & TileMap)
{
	DetermineSightAndCover(TileMap, Source, Target);
	return BlockedOrObstructed;
}