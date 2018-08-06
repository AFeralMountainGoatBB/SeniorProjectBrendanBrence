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
			if (!Map[x][y].getPassableTileType())
			{
				walls.insert(GraphLocation{ x, y });
			}
			else if (Map[x][y].EntityPresent())
			{
				//std::cout << "Entity being added to " << x << "," << y << std::endl;
				Entities.insert(GraphLocation{ x,y });
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
			auto temp = std::make_pair(next, 1.0);
			//check if entity there and add 999.0 to cost if they are there
			if (EntityPresent(next))
			{
				//std::cout << "Entity Present in " << next.x << "," << next.y << std::endl;
				temp.second += 999.0;
			}
			//checking if diagonal
			if (abs(direction.x) == abs(direction.y))
			{
				GraphLocation Vertical{ id.x + direction.x, id.y };
				GraphLocation Horizontal{ id.x, id.y + direction.y };
				if (passable(Vertical) == true && passable(Horizontal) == true)
				{
					//diag movement costs 1.5, instead of 1.0
					temp.second += .5;
					results.push_back(temp);
				}
			}
			else
			{
				//no changes needed to temp
				results.push_back(temp);
			}
		}//end if in graph and passable
	}

	if ((id.x + id.y) % 2 == 0) {
		std::reverse(results.begin(), results.end());
	}
	return results;
}
