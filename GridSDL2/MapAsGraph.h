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

	//each node follows these 'cardinal' m_directions in the map
	//std::vector <std::pair<int, int>> m_directions = { {0,1}, {1,1}, {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };
};

class MapAsGraph {
	//std::vector<GraphLocation> AllNodes;
	
	//will generate starting north->northwest->west, etc, so odd indexes are diagonals, and cost more movement, 
	//will always have 8 neighbors, neighbors that cannot be moved to have the weight (double) set to infinity
	//std::map<std::pair<double, GraphLocation>, std::vect> Neighbors = {};

public:
	bool InGraph(GraphLocation loc) const {
		return ((0 <= loc.x) && (loc.x < m_width) && (0 <= loc.y) && (loc.y < m_height));
	}

	bool passable(GraphLocation id) const {
		return m_walls.find(id) == m_walls.end();
	}
	
	bool EntityPresent(GraphLocation id) const {
		return !(m_Entities.find(id) == m_Entities.end());
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

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

	std::set<GraphLocation>& GetWalls() { return m_walls; }
	std::set<GraphLocation>& GetEntities() { return m_Entities; }

private:
	static std::vector<GraphLocation> m_directions;
	int m_width = g_LEVEL_WIDTH / g_TILE_WIDTH;
	int m_height = g_LEVEL_HEIGHT / g_TILE_HEIGHT;
	std::set<GraphLocation> m_walls;
	std::set<GraphLocation> m_Entities;
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
