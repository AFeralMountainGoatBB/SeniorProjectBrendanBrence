#include "MapAlgorithms.h"


void SightAlgorithm::DetermineSightAndCover(std::vector<std::vector<Tile>> & TileMap, std::pair<int, int> Source, std::pair<int, int> Target)
{
	//pair corners
	/*
	GeneratePairs(Source, Target);
	//find each corner and check if obstructed, or has cover or not.
	for (auto it = PairsToCheck.begin(); it != PairsToCheck.end(); it++)
	{
		std::pair<bool, bool> TempBool (false, false);
		if ((*it).first == FindTopLeft(Source))
		{
			TempBool = raytrace((*it).first, (*it).second, TileMap);
			if (TempBool.first == false)
			{
				TopLeft.first = false;
			}
			if (TempBool.second == true)
			{
				TopLeft.second = true;
			}
			//TopLeft;
		}

		if ((*it).first == FindTopRight(Source))
		{
			TempBool = raytrace((*it).first, (*it).second, TileMap);
			if (TempBool.first == false)
			{
				TopRight.first = false;
			}
			if (TempBool.second == true)
			{
				TopRight.second = true;
			}
		}

		if ((*it).first == FindBottomLeft(Source))
		{
			TempBool = raytrace((*it).first, (*it).second, TileMap);
			if (TempBool.first == false)
			{
				BottomLeft.first = false;
			}
			if (TempBool.second == true)
			{
				BottomLeft.second = true;
			}
		}

		if ((*it).first == FindBottomRight(Source))
		{
			TempBool = raytrace((*it).first, (*it).second, TileMap);
			if (TempBool.first == false)
			{
				BottomRight.first = false;
			}
			if (TempBool.second == true)
			{
				BottomRight.second = true;
			}
		}
	}
	*/

	//alternate way, just calculate from center to center
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
	/*bool Obstructed = true;
	bool Blocked = true;
	//call determine sight and cover which will do just that for each corner
	DetermineSightAndCover(TileMap, Source, Target);
	//interpret results for each corner's blocked and return if blocked
	if (TopLeft.first == false)
	{
		Blocked = false;
	}
	if (TopLeft.second == false)
	{
		Obstructed = false;
		Blocked = false;
		return (std::make_pair(Blocked, Obstructed));
	}
	if (TopRight.first == false)
	{
		Blocked = false;
	}
	if (TopRight.second == false)
	{
		Obstructed = false;
		Blocked = false;
		return (std::make_pair(Blocked, Obstructed));
	}

	if (BottomLeft.first == false)
	{
		Blocked = false;
	}

	if (BottomLeft.second == false)
	{
		Obstructed = false;
		Blocked = false;
		return (std::make_pair(Blocked, Obstructed));
	}

	if (BottomRight.first == false)
	{
		Blocked = false;
	}

	if (BottomRight.second == false)
	{
		Obstructed = false;
		Blocked = false;
		return (std::make_pair(Blocked, Obstructed));
	}

	return std::make_pair(false, false);*/
	DetermineSightAndCover(TileMap, Source, Target);
	return BlockedOrObstructed;
}

float SightAlgorithm::FindSlope(std::pair<int, int> Source, std::pair<int, int> Target)
{
	return 0.0;
}

std::pair<int, int> SightAlgorithm::PixelToGrid(std::vector<std::vector<Tile>>&TileMap, std::pair<int, int> Source)
{
	int GridX = std::floor(Source.first / TILE_WIDTH);
	int GridY = std::floor(Source.second / TILE_HEIGHT);
	return std::make_pair(GridX, GridY);
}

void SightAlgorithm::GeneratePairs(std::pair<int, int> Source, std::pair<int, int> Target)
{
	PairsToCheck.push_back(std::make_pair(FindTopLeft(Source), FindTopLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopLeft(Source), FindTopRight(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopLeft(Source), FindBottomLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopLeft(Source), FindBottomRight(Target)));

	PairsToCheck.push_back(std::make_pair(FindTopRight(Source), FindTopLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopRight(Source), FindTopRight(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopRight(Source), FindBottomLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindTopRight(Source), FindBottomRight(Target)));

	PairsToCheck.push_back(std::make_pair(FindBottomLeft(Source), FindTopLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomLeft(Source), FindTopRight(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomLeft(Source), FindBottomLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomLeft(Source), FindBottomRight(Target)));

	PairsToCheck.push_back(std::make_pair(FindBottomRight(Source), FindTopLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomRight(Source), FindTopRight(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomRight(Source), FindBottomLeft(Target)));
	PairsToCheck.push_back(std::make_pair(FindBottomRight(Source), FindBottomRight(Target)));

	for (auto i = PairsToCheck.begin(); i < PairsToCheck.end(); i++)
	{
		std::cout << "(" << (*i).first.first << "," << (*i).first.second << ")";
		std::cout << " , ";
		std::cout << "(" << (*i).second.first << "," << (*i).second.second << ")" << std::endl;
	}
}

std::pair<double, double> SightAlgorithm::FindTopLeft(std::pair<int, int> Source)
{
	double xval;
	double yval;
	/*
	xval = (Source.first * TILE_WIDTH);
	yval = (Source.second * TILE_WIDTH);
	*/
	xval = Source.first+.01;
	yval = Source.second+.01;
	return (std::make_pair(xval, yval));
}
std::pair<double, double> SightAlgorithm::FindTopRight(std::pair<int, int> Source)
{
	double xval;
	double yval;
	/*
	xval = ((Source.first+1) * TILE_WIDTH)-1;
	yval = (Source.second*TILE_HEIGHT);
	*/
	xval = Source.first + 1-.01;
	yval = Source.second+.01;
	return (std::make_pair(xval, yval));
}
std::pair<double, double> SightAlgorithm::FindBottomLeft(std::pair<int, int> Source)
{
	double xval;
	double yval;
	/*
	xval = ((Source.first) * TILE_WIDTH);
	yval = ((Source.second + 1)*TILE_HEIGHT) - 1;
	*/
	xval = Source.first+.01;
	yval = Source.second + 1-.01;
	return (std::make_pair(xval, yval));
}
std::pair<double, double> SightAlgorithm::FindBottomRight(std::pair<int, int> Source)
{
	double xval;
	double yval;
	/*
	xval = ((Source.first + 1) * TILE_WIDTH) - 1;
	yval = ((Source.second+1)*TILE_HEIGHT)-1;
	*/
	xval = Source.first + 1-.01;
	yval = Source.second + 1-.01;
	return (std::make_pair(xval, yval));
}
