#include "GeneralHeaders.h"
#include "MapAsGraph.h"
#include <queue>

class Tile;
//will attempt to use modified A* algorithm, have seperate class for heirustic calculation and A* calculations seperately

class PathFinder
{
public:
	std::map<GraphLocation, GraphLocation> breadth_first_search(MapAsGraph graph, GraphLocation start);

	std::vector<GraphLocation> reconstruct_path(GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation> came_from);

	void DisplayPath(std::vector<GraphLocation> path);

	void TestBreadthFirst(std::vector<std::vector<Tile>>& Map, int x, int y);

	void dijkstra_search(MapAsGraph graph, GraphLocation start, GraphLocation goal, std::map<GraphLocation, GraphLocation>& came_from, std::map<GraphLocation, double>& cost_so_far);

	void TestDijkstra(std::vector<std::vector<Tile>>&Map, int x, int y);
	
	void draw_grid(MapAsGraph& graph, int field_width, std::map<GraphLocation, double>* distances = nullptr, std::map<GraphLocation, GraphLocation>* point_to = nullptr, std::vector<GraphLocation>* path = nullptr);

private:

	std::map <GraphLocation, GraphLocation> came_from_graph;
};
