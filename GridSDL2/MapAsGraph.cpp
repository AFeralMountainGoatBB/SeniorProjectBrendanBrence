#include "MapAsGraph.h"
#include "Tile.h"

std::vector<GraphLocation> MapAsGraph::directions = {
	GraphLocation{ 1, 0 }, GraphLocation{ 1, 1 }, GraphLocation{ 0, -1 },  GraphLocation{ -1, -1 },
	GraphLocation{ -1, 0 },  GraphLocation{ 1, -1 }, GraphLocation{ 0, 1 },  GraphLocation{ -1, 1 }, };

void MapAsGraph::MapToGraph(std::vector<std::vector<Tile>>& Map)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (!Map[x][y].getPassable())
			{
				walls.insert(GraphLocation{ x, y });
			}
		}
	}
}

std::vector<std::pair<GraphLocation, double>> MapAsGraph:: Getneighbors(GraphLocation id)
{
	std::vector<std::pair<GraphLocation, double>> results;
	for (GraphLocation direction : directions) {
		GraphLocation next{ id.x + direction.x, id.y + direction.y };
		if (InGraph(next) && passable(next)) {

			//checking if diagonal
			if (abs(direction.x) == abs(direction.y))
			{
				GraphLocation Vertical{ id.x + direction.x, id.y };
				GraphLocation Horizontal{ id.x, id.y + direction.y };
				if (passable(Vertical) == true && passable(Horizontal) == true)
				{
					//diag movement costs 1.5, instead of 1.0
					auto temp = std::make_pair(next, 1.5);
					results.push_back(temp);
				}
			}
			else
			{
				auto temp = std::make_pair(next, 1.0);
				results.push_back(temp);
			}
		}
	}

	if ((id.x + id.y) % 2 == 0) {
		std::reverse(results.begin(), results.end());
	}
	return results;
}
