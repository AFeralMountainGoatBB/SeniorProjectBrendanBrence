#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

class Tile;

struct GraphLocation {
	//x and y locations in the graph
	int x;
	int y;
	GraphLocation(int xin, int yin) { x = xin; y = yin; }
	GraphLocation() { x = 0; y = 0; }
	//distance from target to node
	//int distance;

	//each node follows these 'cardinal' directions in the map
	//std::vector <std::pair<int, int>> directions = { {0,1}, {1,1}, {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };
};

class MapAsGraph {
	//std::vector<GraphLocation> AllNodes;
	
	//will generate starting north->northwest->west, etc, so odd indexes are diagonals, and cost more movement, 
	//will always have 8 neighbors, neighbors that cannot be moved to have the weight (double) set to infinity
	//std::map<std::pair<double, GraphLocation>, std::vect> Neighbors = {};

public:
	bool InGraph(GraphLocation loc) const {
		return ((0 <= loc.x) && (loc.x < width) && (0 <= loc.y) && (loc.y < height));
	}

	bool passable(GraphLocation id) const {
		return walls.find(id) == walls.end();
	}
	
	bool EntityPresent(GraphLocation id) const {
		return !(Entities.find(id) == Entities.end());
	}

	double cost(GraphLocation& from, GraphLocation& to)
	{
		//check differences in positon to determine if diagonal
		int DeltaX = from.x - to.x;
		int DeltaY = from.y - to.y;
		//checking if diagonal
		if(abs(DeltaX) == abs(DeltaY))
		{
			return 1.5;
		}
		else
		{
			return 1.0;
		}
	}

	void MapToGraph(std::vector<std::vector<Tile>>&Map);

	std::vector<std::pair<GraphLocation, double>> Getneighbors(GraphLocation id);

	int GetHeight() { return height; }
	int GetWidth() { return width; }

	std::set<GraphLocation>& GetWalls() { return walls; }
	std::set<GraphLocation>& GetEntities() { return Entities; }

private:
	static std::vector<GraphLocation> directions;
	int width = g_LEVEL_WIDTH / g_TILE_WIDTH;
	int height = g_LEVEL_HEIGHT / g_TILE_HEIGHT;
	std::set<GraphLocation> walls;
	std::set<GraphLocation> Entities;
};

static bool operator < (GraphLocation a, GraphLocation b) {
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

static bool operator == (GraphLocation a, GraphLocation b) {
	return a.x == b.x && a.y == b.y;
}

static bool operator != (GraphLocation a, GraphLocation b) {
	return !(a == b);
}
