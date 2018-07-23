#include "PathfindingAlgorithm.h"
#include "Tile.h"
#include <iomanip>
#include <queue>
//for ease of syntax since the pair is LOCATION then COST
typedef std::pair<GraphLocation, double> LocationCost;

void PathFinder::TestBreadthFirst(std::vector<std::vector<Tile>>& Map, int x, int y)
{
	GraphLocation Start(x, y);
	GraphLocation End(15, 11);
	MapAsGraph CurrentGraph;
	CurrentGraph.MapToGraph(Map);
	auto temp = breadth_first_search(CurrentGraph, Start);

	DisplayPath(reconstruct_path(Start, End, temp));
}

std::map<GraphLocation, GraphLocation> PathFinder:: breadth_first_search(MapAsGraph graph, GraphLocation start) {
	std::queue<GraphLocation> frontier;
	frontier.push(start);

	std::map<GraphLocation, GraphLocation> came_from;
	came_from[start] = start;

	while (!frontier.empty()) {
		GraphLocation current = frontier.front();
		frontier.pop();

		auto tempgraph1 = graph.Getneighbors(current);
		std::vector<GraphLocation> TempGraph2;
		for (auto it = tempgraph1.begin(); it != tempgraph1.end(); it++)
		{
			TempGraph2.push_back((*it).first);
		}
		for (GraphLocation next : TempGraph2)
		{
			if (came_from.find(next) == came_from.end())
			{
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

//this operator is backwards and scoped to only this file, it is for reversing the priority queue
static bool operator <(LocationCost &a, LocationCost &b)
{
	//remember locationcost.first is graphlocation, locationcost.second is double
	if (a.second >= b.second)
	{
		return true;
	}
	if (a.second < b.second)
	{
		return false;
	}
}

void PathFinder::dijkstra_search (MapAsGraph graph, GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation>& came_from, std::map<GraphLocation, double>& cost_so_far)
{
	std::priority_queue<LocationCost> frontier;
	std::pair<GraphLocation, double> StartLC = std::make_pair(start, 0.0);
	frontier.push(StartLC);

	came_from[start] = start;
	cost_so_far[start] = 0;
	
	while (!frontier.empty()) {
		GraphLocation current = frontier.top().first;
		frontier.pop();
		if (current == goal) {
			break;
		}
		auto TempGraph = graph.Getneighbors(current);
		std::cout << "     x:" << current.x << " y:" << current.y << "Neighbors:" << std::endl;
		for (auto it = TempGraph.begin(); it != TempGraph.end(); it++)
		{
			std::cout << "x:" << (*it).first.x << "  y:" << (*it).first.y << std::endl;
		}
		for (auto it = TempGraph.begin(); it != TempGraph.end(); it++)
		{
			double new_cost = cost_so_far[current] + (*it).second;
			if (cost_so_far.find((*it).first) == cost_so_far.end() || new_cost < cost_so_far[(*it).first]) 
			{
				cost_so_far[(*it).first] = new_cost;
				came_from[(*it).first] = current;
				frontier.emplace((*it).first, new_cost);
			}
		}
	}
}

void PathFinder::TestDijkstra(std::vector<std::vector<Tile>>&Map, int x, int y)
{
	GraphLocation Start(x, y);
	GraphLocation End(15, 11);
	MapAsGraph CurrentGraph;
	CurrentGraph.MapToGraph(Map);
	std::map<GraphLocation, double> cost_so_far;
	dijkstra_search(CurrentGraph, Start, End, came_from_graph, cost_so_far);
	DisplayPath(reconstruct_path(Start, End, came_from_graph));
	draw_grid(CurrentGraph, 5, &cost_so_far, nullptr);
}

void PathFinder::draw_grid(MapAsGraph& graph, int field_width, std::map<GraphLocation, double>* distances, std::map<GraphLocation, GraphLocation>* point_to, std::vector<GraphLocation>* path) {
	std::cout << "Displaying grid" << std::endl;
	for (int y = 0; y != graph.GetHeight(); ++y) {
		for (int x = 0; x != graph.GetWidth(); ++x) {
			GraphLocation id{ x, y };
			std::cout << std::left << std::setw(field_width);
			//std::cout << "left width set" << std::endl;
			if (graph.GetWalls().find(id) != graph.GetWalls().end()) {
				std::cout << std::string(field_width, '#');
			}
			else if (point_to != nullptr && point_to->count(id)) 
			{
				GraphLocation next = (*point_to)[id];
				if (next.x == x + 1) { std::cout << "> "; }
				else if (next.x == x - 1) { std::cout << "< "; }
				else if (next.y == y + 1) { std::cout << "v "; }
				else if (next.y == y - 1) { std::cout << "^ "; }
				else { std::cout << "* "; }
			}
			else if (distances != nullptr && distances->count(id)) {
				std::cout << (*distances)[id];
			}
			else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
				std::cout << '@';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
}

std::vector<GraphLocation> PathFinder::reconstruct_path(GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation> came_from) {
	std::vector<GraphLocation> path;
	GraphLocation current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

void PathFinder::DisplayPath(std::vector<GraphLocation> path)
{
	for (auto it = path.begin(); it != path.end(); it++)
	{
		std::cout << "x:" << (*it).x << "  y:" << (*it).y << std::endl;
	}
}