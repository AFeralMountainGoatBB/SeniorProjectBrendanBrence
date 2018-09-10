/**********************************************************************************************//**
 * @file	PathfindingAlgorithm.h.
 *
 * @brief	Declares the pathfinding algorithm class
 * 			
 * @author Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
 **************************************************************************************************/

#include "GeneralHeaders.h"
#include "MapAsGraph.h"
#include <queue>

//fwd declaration of tile to prevent circular dependencies
class Tile;

/**********************************************************************************************//**
 * @class	PathFinder
 *
 * @brief	class to hold algorithms for pathfinding
 *
 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
 * @date	9/3/2018
 **************************************************************************************************/

class PathFinder
{
public:

	/**********************************************************************************************//**
	 * @fn	std::vector<GraphLocation> PathFinder::reconstruct_path(GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation> came_from);
	 *
	 * @brief	Reconstruct path  - construct a vector of graphlocations starting at the end and working way to the beginning using came_from
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	start	 	The start node
	 * @param	goal	 	The goal node
	 * @param	came_from	The came from vector, used to track the shortest path back to the beginning
	 *
	 * @return	A vector of graphlocations that make out a path from the start to beginning
	 **************************************************************************************************/

	std::vector<GraphLocation> reconstruct_path(GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation> came_from);

	/**********************************************************************************************//**
	 * @fn	void PathFinder::DisplayPath(std::vector<GraphLocation> path);
	 *
	 * @brief	Displays a path described by path to console
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	path	Full path
	 **************************************************************************************************/

	void DisplayPath(std::vector<GraphLocation> path);

	/**********************************************************************************************//**
	 * @fn	void PathFinder::dijkstra_search(MapAsGraph graph, GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation>& came_from, std::map<GraphLocation, double>& cost_so_far);
	 *
	 * @brief	Dijkstra search, weighted dijkstra's search, uses a priority queue to find the shortest path to goal from start
	 * 			keeps track of the cost to advance in the direction that costs the least every iteration
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param 		  	graph	   	The graph pathfinding is on
	 * @param 		  	start	   	The start node
	 * @param 		  	goal	   	The goal node to be reached
	 * @param [in,out]	came_from  	The came from map that will be constructed
	 * @param [in,out]	cost_so_far	The cost so far map to keep track of what it costs to move from location to location
	 **************************************************************************************************/

	void dijkstra_search(MapAsGraph graph, GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation>& came_from, std::map<GraphLocation, double>& cost_so_far);

	/**********************************************************************************************//**
	 * @fn	void PathFinder::draw_grid(MapAsGraph& graph, int field_width, std::map<GraphLocation, double>* distances = nullptr, std::map<GraphLocation, GraphLocation>* point_to = nullptr, std::vector<GraphLocation>* path = nullptr);
	 *
	 * @brief	Draw grid to console
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	graph	   	The graph
	 * @param 		  	field_width	Width of the field.
	 * @param [in,out]	distances  	(Optional) If non-null, the distances.
	 * @param [in,out]	point_to   	(Optional) If non-null, the point
	 * @param [in,out]	path	   	(Optional) If non-null, full pathname of the file.
	 **************************************************************************************************/

	void draw_grid(MapAsGraph& graph, int field_width, std::map<GraphLocation, double>* distances = nullptr, std::map<GraphLocation, GraphLocation>* point_to = nullptr, std::vector<GraphLocation>* path = nullptr);

	/**********************************************************************************************//**
	 * @fn	std::vector<GraphLocation> PathFinder::UseDijkstra(std::vector<std::vector<Tile>>&TileMap, int xSource, int ySource, int xGoal, int yGoal);
	 *
	 * @brief	Use dijkstra function sets up the class and executes the required functions to execute a dikstra search
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param [in,out]	TileMap	The tile map.
	 * @param 		  	xSource	x val source node
	 * @param 		  	ySource	y val source node
	 * @param 		  	xGoal  	The x val of the goal
	 * @param 		  	yGoal  	The y value of the goal.
	 *
	 * @return	A vector of graph locations that is the shortest path found by the search
	 **************************************************************************************************/

	std::vector<GraphLocation> UseDijkstra(std::vector<std::vector<Tile>>&TileMap, int xSource, int ySource, int xGoal, int yGoal);

	/**********************************************************************************************//**
	 * @fn	int PathFinder::GetTotalDistance(int xGoal, int yGoal);
	 *
	 * @brief	Gets total distance
	 *
	 * @author	Code Adapted from https://www.redblobgames.com/ various examples by Brendan B
	 * @date	9/3/2018
	 *
	 * @param	xGoal	x val for The goal
	 * @param	yGoal	y val for The goal.
	 *
	 * @return	The total distance of the path to the goal
	 **************************************************************************************************/

	int GetTotalDistance(int xGoal, int yGoal);

private:
	/** @brief Map structure to map node to shortest came from node, in order to construct shortest path**/
	std::map <GraphLocation, GraphLocation> m_came_from_graph;
	/** @brief	The cost so far */
	std::map<GraphLocation, double> m_cost_so_far;
};
