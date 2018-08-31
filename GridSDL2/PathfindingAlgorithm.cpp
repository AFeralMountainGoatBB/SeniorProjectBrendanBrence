#include "PathfindingAlgorithm.h"
#include "Tile.h"
#include <iomanip>
#include <queue>
//for ease of syntax since the pair is LOCATION then COST
typedef std::pair<GraphLocation, double> LocationCost;

void PathFinder::TestBreadthFirst(std::vector<std::vector<Tile>>& a_Map, int a_x, int a_y)
{
	GraphLocation Start(a_x, a_y);
	GraphLocation End(15, 11);
	MapAsGraph CurrentGraph;
	CurrentGraph.MapToGraph(a_Map);
	auto temp = breadth_first_search(CurrentGraph, Start);

	DisplayPath(reconstruct_path(Start, End, temp));
}

std::map<GraphLocation, GraphLocation> PathFinder:: breadth_first_search(MapAsGraph a_graph, GraphLocation a_start) {
	std::queue<GraphLocation> frontier;
	frontier.push(a_start);

	std::map<GraphLocation, GraphLocation> came_from;
	came_from[a_start] = a_start;

	while (!frontier.empty()) {
		GraphLocation current = frontier.front();
		frontier.pop();

		auto tempgraph1 = a_graph.Getneighbors(current);
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
static bool operator <(LocationCost &a_a, LocationCost &a_b)
{
	//remember locationcost.first is graphlocation, locationcost.second is double
	if (a_a.second >= a_b.second)
	{
		return true;
	}
	if (a_a.second < a_b.second)
	{
		return false;
	}
}

void PathFinder::dijkstra_search (MapAsGraph a_graph, GraphLocation a_start, GraphLocation a_goal, std::map<GraphLocation, GraphLocation>& a_came_from, std::map<GraphLocation, double>& a_cost_so_far)
{
	std::priority_queue<LocationCost> frontier;
	std::pair<GraphLocation, double> StartLC = std::make_pair(a_start, 0.0);
	frontier.push(StartLC);

	a_came_from[a_start] = a_start;
	a_cost_so_far[a_start] = 0;
	
	while (!frontier.empty()) {
		GraphLocation current = frontier.top().first;
		frontier.pop();
		if (current == a_goal) {
			break;
		}
		auto TempGraph = a_graph.Getneighbors(current);
		//std::cout << "     a_x:" << current.a_x << " a_y:" << current.a_y << "Neighbors:" << std::endl;
		//for (auto it = TempGraph.begin(); it != TempGraph.end(); it++)
		//{
		//	std::cout << "a_x:" << (*it).first.a_x << "  a_y:" << (*it).first.a_y << std::endl;
		//}
		for (auto it = TempGraph.begin(); it != TempGraph.end(); it++)
		{
			double new_cost = a_cost_so_far[current] + (*it).second;
			if (a_cost_so_far.find((*it).first) == a_cost_so_far.end() 
				||
				new_cost < a_cost_so_far[(*it).first]) 
			{
				a_cost_so_far[(*it).first] = new_cost;
				a_came_from[(*it).first] = current;
				frontier.emplace((*it).first, new_cost);
			}
		}
	}
}

void PathFinder::TestDijkstra(std::vector<std::vector<Tile>>&a_Map, int a_x, int a_y)
{
	GraphLocation Start(a_x, a_y);
	GraphLocation End(15, 11);
	MapAsGraph CurrentGraph;
	CurrentGraph.MapToGraph(a_Map);
	dijkstra_search(CurrentGraph, Start, End, m_came_from_graph, m_cost_so_far);
	DisplayPath(reconstruct_path(Start, End, m_came_from_graph));
	draw_grid(CurrentGraph, 5, &m_cost_so_far, nullptr);
}

void PathFinder::draw_grid(MapAsGraph& a_graph, int a_field_width, std::map<GraphLocation, double>* a_distances, std::map<GraphLocation, GraphLocation>* a_point_to, std::vector<GraphLocation>* a_path) {
	std::cout << "Displaying grid" << std::endl;
	for (int y = 0; y != a_graph.GetHeight(); ++y) {
		for (int x = 0; x != a_graph.GetWidth(); ++x) {
			GraphLocation id{ x, y };
			std::cout << std::left << std::setw(a_field_width);
			//std::cout << "left m_width set" << std::endl;
			if (a_graph.GetWalls().find(id) != a_graph.GetWalls().end()) {
				std::cout << std::string(a_field_width, '#');
			}
			else if (a_graph.GetEntities().find(id)!=a_graph.GetEntities().end()) 
			{
				std::cout << "%";
			}
			else if (a_point_to != nullptr && a_point_to->count(id)) 
			{
				GraphLocation next = (*a_point_to)[id];
				if (next.x == x + 1) { std::cout << "> "; }
				else if (next.x == x - 1) { std::cout << "< "; }
				else if (next.y == y + 1) { std::cout << "v "; }
				else if (next.y == y - 1) { std::cout << "^ "; }
				else { std::cout << "* "; }
			}
			else if (a_distances != nullptr && a_distances->count(id)) {
				std::cout << (*a_distances)[id];
			}
			else if (a_path != nullptr && find(a_path->begin(), a_path->end(), id) != a_path->end()) {
				std::cout << '@';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
}

std::vector<GraphLocation> PathFinder::reconstruct_path(GraphLocation a_start, GraphLocation a_goal, std::map<GraphLocation, GraphLocation> a_came_from) {
	std::vector<GraphLocation> path;
	GraphLocation current = a_goal;
	while (current != a_start) {
		path.push_back(current);
		current = a_came_from[current];
	}
	path.push_back(a_start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

void PathFinder::DisplayPath(std::vector<GraphLocation> a_path)
{
	for (auto it = a_path.begin(); it != a_path.end(); it++)
	{
		std::cout << "a_x:" << (*it).x << "  a_y:" << (*it).y << std::endl;
	}
}

std::vector<GraphLocation> PathFinder::UseDijkstra(std::vector<std::vector<Tile>>&a_TileMap, int a_xSource, int a_ySource, int a_xGoal, int a_yGoal)
{
	GraphLocation Start(a_xSource, a_ySource);
	GraphLocation End(a_xGoal, a_yGoal);
	MapAsGraph CurrentGraph;
	CurrentGraph.MapToGraph(a_TileMap);
	//std::cout << "CurrentGraphMade" << std::endl;
	dijkstra_search(CurrentGraph, Start, End, m_came_from_graph, m_cost_so_far);
	DisplayPath(reconstruct_path(Start, End, m_came_from_graph));
	//draw_grid(CurrentGraph, 5, &a_cost_so_far, nullptr);
	return reconstruct_path(Start, End, m_came_from_graph);
}

int PathFinder:: GetTotalDistance(int a_xGoal, int a_yGoal)
{
	GraphLocation Goal = { a_xGoal, a_yGoal };
	int TempCost = m_cost_so_far[Goal];
	return TempCost;
}

