#include "MapAlgorithms.h"


void SightAlgorithm::DetermineSightAndCover(std::vector<std::vector<Tile>> & a_TileMap, std::pair<int, int> a_Source, std::pair<int, int> a_Target)
{
	m_BlockedOrObstructed = raytrace(std::make_pair(a_Source.first, a_Source.second), std::make_pair(a_Target.first, a_Target.second), a_TileMap);
}

std::pair<bool, bool> SightAlgorithm::raytrace(std::pair<int, int> a_Source, std::pair<int, int> a_Target, std::vector<std::vector<Tile>> & a_TileMap)
{
	std::pair<bool, bool> BlockedObstructed;
	std::pair<bool, bool> TempBool;
		int dx = abs(a_Target.first - a_Source.first);
		int dy = abs(a_Target.second - a_Source.second);
		int x = a_Source.first;
		int y = a_Source.second;
		int n = 1 + dx + dy;
		int x_inc = (a_Target.first > a_Source.first) ? 1 : -1;
		int y_inc = (a_Target.second > a_Source.second) ? 1 : -1;
		int error = dx - dy;
		dx *= 2;
		dy *= 2;

		for (; n > 0; --n)
		{
			//this statement checks to see if we are looking at the start or end tiles, two tiles that should not be checked for obstructions or blocking
			if (((x == a_Source.first && y == a_Source.second) || (x == a_Target.first && y == a_Target.second))==false)
			{
				std::cout << "a_x:" << x << " a_y:" << y << std::endl;
				TempBool = CheckTile(x, y, a_TileMap);
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

std::pair<bool, bool> SightAlgorithm:: CheckTile(int a_x, int a_y, std::vector<std::vector<Tile>> & a_TileMap)
{
	bool block;
	bool obstructed;
	if (a_TileMap[a_x][a_y].getType()>g_TILE_STONE && a_TileMap[a_x][a_y].getType()!=g_TILE_WATER)
	{
		block = true;
	}
	if (a_TileMap[a_x][a_y].EntityPresent())
	{
		obstructed = true;
	}
	return (std::make_pair(block, obstructed));
}

std::pair<bool,bool> SightAlgorithm::CheckAll(std::pair<int, int> a_Source, std::pair<int, int> a_Target, std::vector<std::vector<Tile>> & a_TileMap)
{
	DetermineSightAndCover(a_TileMap, a_Source, a_Target);
	return m_BlockedOrObstructed;
}