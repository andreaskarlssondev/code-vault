#pragma once

#include <queue>
#include <unordered_map>

class Grid;

struct GridLocation
{
	GridLocation() : x(), y() {}
	GridLocation(int aX, int aY) : x(aX), y(aY) {}

	bool operator==(const GridLocation& aOtherGridLocation) const
	{
		return x == aOtherGridLocation.x && y == aOtherGridLocation.y;
	}

	int x;
	int y;

	struct HashFunction
	{
		size_t operator()(const GridLocation& aGridLocation) const noexcept
		{
			return aGridLocation.x + INT_MAX * aGridLocation.y;
		}
	};
};

struct CellCost
{
	int gCost;
	int hCost;

	GridLocation location;

	int Cost() const
	{
		return gCost + hCost;
	}

	bool operator<(const CellCost& other) const
	{
		return Cost() > other.Cost(); // For priority queue (min-heap)
	}
};


class AStar 
{

	public:
		std::vector<GridLocation> FindPath(Grid& aSearchGrid, GridLocation aStartLocation, GridLocation aGoalLocation);

	private:

		/* Manhattan */
		int Heuristic(GridLocation& aLocation, GridLocation& aSecondLocation);

		std::vector<GridLocation> BuildPath(std::unordered_map<GridLocation, GridLocation, GridLocation::HashFunction> aSearchedPath, GridLocation aGoalLocation);

};
