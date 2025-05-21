#include "AStar.h"

std::vector<GridLocation> AStar::FindPath(Grid& aSearchGrid, GridLocation aStartLocation, GridLocation aGoalLocation)
{
	std::priority_queue<CellCost> frontier;
	std::unordered_map<GridLocation, GridLocation, GridLocation::HashFunction> path;
	std::unordered_map<GridLocation, int, GridLocation::HashFunction> costSoFar;

	while (!frontier.empty())
	{
		CellCost current = frontier.top();
		frontier.pop();

		if (current.location == aGoalLocation)
		{
			return BuildPath(path, aGoalLocation);
		}

		int tentativeGCost = current.gCost + 1;

		for (auto& next : aSearchGrid.GetNeighbors(current.location))
		{
			if (!aSearchGrid.GetCell(next).walkable)
			{
				continue;
			}

			int heurisitcCost = Heuristic(next, aGoalLocation);
			if (costSoFar.find(next) == costSoFar.end() || (tentativeGCost + heurisitcCost) < costSoFar[next])
			{
				costSoFar[next] = tentativeGCost + heurisitcCost;
				frontier.push(CellCost{ tentativeGCost, heurisitcCost, next });
				path[next] = current.location;
			}

		}

	}

	// No Path
	return {};
}

std::vector<GridLocation> AStar::BuildPath(std::unordered_map<GridLocation, GridLocation, GridLocation::HashFunction> aSearchedPath, GridLocation aGoalLocation)
{
	std::vector<GridLocation> path;

	auto it = aSearchedPath.find(aGoalLocation);

	while (it != aSearchedPath.end())
	{
		if (it->first == it->second)
		{
			break;
		}

		path.push_back(it->second);
		it = aSearchedPath.find(it->second);
	}
	path.erase(path.begin() + path.size() - 1);

	return path;
}


int AStar::Heuristic(GridLocation& aLocation, GridLocation& aSecondLocation)
{
	return abs(aLocation.x - aSecondLocation.x) + abs(aLocation.y - aSecondLocation.y);
}