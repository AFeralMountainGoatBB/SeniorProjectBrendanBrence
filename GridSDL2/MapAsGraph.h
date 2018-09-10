/**********************************************************************************************//**
 * @file	MapAsGraph.h.
 *
 * @brief	Declares the map as graph class, and operators to be used in their functions
 * 			
 * @author - Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 **************************************************************************************************/

#pragma once
#include "GeneralHeaders.h"
#include "SharedEnums.h"

//fwd declaration to avoid circular dependencies
class Tile;

/**********************************************************************************************//**
 * @struct	GraphLocation
 *
 * @brief	A graph location, used to store information on created graphs
 *
 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 * @date	9/3/2018
 **************************************************************************************************/

struct GraphLocation {
	/** @brief	The x coordinate */
	int x;
	/** @brief	The y coordinate */
	int y;

	/**********************************************************************************************//**
	 * @fn	GraphLocation(int xin, int yin)
	 *
	 * @brief	Constructor
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	xin	The xin.
	 * @param	yin	The yin.
	 **************************************************************************************************/

	GraphLocation(int xin, int yin) { x = xin; y = yin; }

	/**********************************************************************************************//**
	 * @fn	GraphLocation()
	 *
	 * @brief	Default constructor
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 **************************************************************************************************/

	GraphLocation() { x = 0; y = 0; }
};

/**********************************************************************************************//**
 * @class	MapAsGraph
 *
 * @brief	A map translated to a graph.
 *
 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 * @date	9/3/2018
 **************************************************************************************************/

class MapAsGraph {
	//will generate starting north->northwest->west, etc, so odd indexes are diagonals, and cost more movement, 
	//will always have 8 neighbors, neighbors that cannot be moved to have the weight (double) set to infinity

public:

	/**********************************************************************************************//**
	 * @fn	bool MapAsGraph::InGraph(GraphLocation a_loc) const
	 *
	 * @brief	checks if location is in graph
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	a_loc	The location.
	 * 					
	 * @return	True if location is in the graph, false if it isnt
	 **************************************************************************************************/

	bool InGraph(GraphLocation a_loc) const {
		return ((0 <= a_loc.x) && (a_loc.x < m_width) && (0 <= a_loc.y) && (a_loc.y < m_height));
	}

	/**********************************************************************************************//**
	 * @fn	bool MapAsGraph::passable(GraphLocation a_id) const
	 *
	 * @brief	passable checks the given location for if it is in the walls structure
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	a_id	The identifier, the location searched for
	 *
	 * @return	True if is passable, false if it is  not.
	 **************************************************************************************************/

	bool passable(GraphLocation a_id) const {
		return m_walls.find(a_id) == m_walls.end();
	}

	/**********************************************************************************************//**
	 * @fn	bool MapAsGraph::EntityPresent(GraphLocation a_id) const
	 *
	 * @brief	Entity present, checks to see if an entity is present
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	a_id	The identifier graph location
	 *
	 * @return	True if an entity is present, false if one is not found.
	 **************************************************************************************************/

	bool EntityPresent(GraphLocation id) const {
		return !(m_Entities.find(id) == m_Entities.end());
	}

	/**********************************************************************************************//**
	 * @fn	double MapAsGraph::cost(GraphLocation& from, GraphLocation& to)
	 *
	 * @brief	calculates cost for edge between from and to
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	from	Source graph location.
	 * @param [in,out]	to  	graph location moving to .
	 *
	 * @return	A double, the cost of the edge
	 **************************************************************************************************/

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

	/**********************************************************************************************//**
	 * @fn	void MapAsGraph::MapToGraph(std::vector<std::vector<Tile>>&Map);
	 *
	 * @brief	Map to graph, looks through a map made of tiles and marks the location of every entity and wall
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	Map	The tilemap
	 **************************************************************************************************/

	void MapToGraph(std::vector<std::vector<Tile>>&Map);

	/**********************************************************************************************//**
	 * @fn	std::vector<std::pair<GraphLocation, double>> MapAsGraph::Getneighbors(GraphLocation a_id);
	 *
	 * @brief	Getneighbors the given identifier, calculates the edge nodes connecting to the graphlocation
	 * 			given by a_id and returns them
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	a_id	The identifier of the graph edge nodes are being created for
	 *
	 * @return	A vector of vectors holding the 'neighbors' of this node. Edges calculated in the function
	 **************************************************************************************************/

	std::vector<std::pair<GraphLocation, double>> Getneighbors(GraphLocation id);

	/**********************************************************************************************//**
	 * @fn	int MapAsGraph::GetHeight()
	 *
	 * @brief	Gets the height
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The height
	 **************************************************************************************************/

	int GetHeight() { return m_height; }

	/**********************************************************************************************//**
	 * @fn	int MapAsGraph::GetWidth()
	 *
	 * @brief	Gets the width
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The width.
	 **************************************************************************************************/

	int GetWidth() { return m_width; }

	/**********************************************************************************************//**
	 * @fn	std::set<GraphLocation>& MapAsGraph::GetWalls()
	 *
	 * @brief	Gets the walls
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The walls located on the map
	 **************************************************************************************************/

	std::set<GraphLocation>& GetWalls() { return m_walls; }

	/**********************************************************************************************//**
	 * @fn	std::set<GraphLocation>& MapAsGraph::GetEntities()
	 *
	 * @brief	Gets the entities
	 *
	 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
	 * @date	9/3/2018
	 *
	 * @return	The entities located on the map
	 **************************************************************************************************/

	std::set<GraphLocation>& GetEntities() { return m_Entities; }

private:
	/** @brief	The directions */
	static std::vector<GraphLocation> m_directions;
	/** @brief	The width */
	int m_width = g_LEVEL_WIDTH / g_TILE_WIDTH;
	/** @brief	The height */
	int m_height = g_LEVEL_HEIGHT / g_TILE_HEIGHT;
	/** @brief	The walls */
	std::set<GraphLocation> m_walls;
	/** @brief	The entities */
	std::set<GraphLocation> m_Entities;
};

/**********************************************************************************************//**
 * @fn	static bool operator< (GraphLocation a, GraphLocation b) { return std::tie(a.x, a.y) < std::tie(b.x, b.y);
 *
 * @brief	Less-than comparison operator, reversed for use in a priority queue setting
 *
 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 * @date	9/3/2018
 *
 * @param	a	The first location to compare.
 * @param	b	The second location to compare.
 *
 * @return	True if the first parameter is less than the second.
 **************************************************************************************************/

static bool operator < (GraphLocation a, GraphLocation b) {
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

/**********************************************************************************************//**
 * @fn	static bool operator== (GraphLocation a, GraphLocation b)
 *
 * @brief	Equality operator
 *
 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 * @date	9/3/2018
 *
 * @param	a	The first instance to compare.
 * @param	b	The second instance to compare.
 *
 * @return	True if the parameters are considered equivalent.
 **************************************************************************************************/

static bool operator == (GraphLocation a, GraphLocation b) {
	return a.x == b.x && a.y == b.y;
}

/**********************************************************************************************//**
 * @fn	static bool operator!= (GraphLocation a, GraphLocation b)
 *
 * @brief	Inequality operator
 *
 * @author	Code ADAPTED from https://www.redblobgames.com various examples on pathfinding by Brendan B
 * @date	9/3/2018
 *
 * @param	a	The first instance to compare.
 * @param	b	The second instance to compare.
 *
 * @return	True if the parameters are not considered equivalent.
 **************************************************************************************************/

static bool operator != (GraphLocation a, GraphLocation b) {
	return !(a == b);
}
