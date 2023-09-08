#include "TileMap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void TileMap::LoadTiles(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}

	std::fstream file(fileName);

	int count = 0;
	std::string buffer;

	file >> buffer;
	file >> count;

	mTiles.clear();
	mTiles.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		int isblocked = 0;
		file >> buffer;
		file >> isblocked;

		auto& tile = mTiles.emplace_back();
		tile.isBlocked = isblocked == 1;
		tile.textureId = X::LoadTexture(buffer.c_str());
	}

	file.close();

	mTileWidth = X::GetSpriteWidth(mTiles[0].textureId);
	mTileHeight = X::GetSpriteHeight(mTiles[0].textureId);
}

void TileMap::LoadMap(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
	{
		return;
	}

	std::fstream file(fileName);
	int columns = 0, rows = 0;
	std::string buffer;

	file >> buffer;
	file >> columns;
	file >> buffer;
	file >> rows;

	mColumns = columns;
	mRows = rows;

	mMap.resize(columns * rows);
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			char tileType;
			file >> tileType;
			mMap[ToIndex(c, r, columns)] = tileType - '0';
		}
	}

	file.close();

	mGraph.Initialize(mColumns, mRows);
	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			if (IsBlocked(c, r))
			{
				continue;
			}

			auto GetNeighbor = [&](int c, int r) -> AI::GridBasedGraph::Node*
			{
				if (IsBlocked(c, r))
				{
					return nullptr;
				}
				return mGraph.GetNode(c, r);
			};

			GridBasedGraph::Node* node = mGraph.GetNode(c, r);
			node->neighbors[GridBasedGraph::Direction::North] = GetNeighbor(c, r - 1);
			node->neighbors[GridBasedGraph::Direction::South] = GetNeighbor(c, r + 1);
			node->neighbors[GridBasedGraph::Direction::East] = GetNeighbor(c + 1, r);
			node->neighbors[GridBasedGraph::Direction::West] = GetNeighbor(c - 1, r);
			node->neighbors[GridBasedGraph::Direction::NorthEast] = GetNeighbor(c + 1, r - 1);
			node->neighbors[GridBasedGraph::Direction::NorthWest] = GetNeighbor(c - 1, r - 1);
			node->neighbors[GridBasedGraph::Direction::SouthEast] = GetNeighbor(c + 1, r + 1);
			node->neighbors[GridBasedGraph::Direction::SouthWest] = GetNeighbor(c - 1, r + 1);
		}
	}
}

void TileMap::Render() const
{
	float spriteWidth = X::GetSpriteWidth(mTiles[0].textureId);
	float spriteHeight = X::GetSpriteHeight(mTiles[0].textureId);
	X::Math::Vector2 position;

	for (int r = 0; r < mRows; r++)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			int index = (r * mColumns) + c;
			X::DrawSprite(mTiles[mMap[index]].textureId, position, X::Pivot::TopLeft);
			position.x += spriteWidth;
		}

		position.x = 0.0f;
		position.y += spriteHeight;
	}

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const auto node = mGraph.GetNode(c, r);

			for (const auto neightbor : node->neighbors)
			{
				if (neightbor == nullptr)
				{
					continue;
				}
				const auto a = GetPixelPosition(node->column, node->row);
				const auto b = GetPixelPosition(neightbor->column, neightbor->row);
				X::DrawScreenLine(a, b, X::Colors::DarkGray);
			}
		}
	}

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const auto node = mGraph.GetNode(c, r);
			if (node->parent != nullptr)
			{

				const auto a = GetPixelPosition(node->column, node->row);
				const auto b = GetPixelPosition(node->parent->column, node->parent->row);
				X::DrawScreenLine(a, b, X::Colors::Yellow);
			}
		}
	}
}

Path TileMap::FindPathBFS(int startX, int startY, int endX, int endY)
{
	Path path;
	BFS bfs;

	if (bfs.Run(mGraph, startX, startY, endX, endY))
	{
		const auto& closedList = bfs.GetClosedList();
		auto node = closedList.back();

		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	return path;
}

Path TileMap::FindPathDFS(int startX, int startY, int endX, int endY)
{
	Path path;
	DFS dfs;

	if (dfs.Run(mGraph, startX, startY, endX, endY))
	{
		const auto& closedList = dfs.GetClosedList();
		auto node = closedList.back();

		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	return path;
}

Path TileMap::FindPathDijkstra(int startX, int startY, int endX, int endY)
{
	Path path;
	Dijkstra dijkstra;

	auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
	{
		if (node->column != neighbor->column && node->row != neighbor->row)
		{
			return 1.7f;
		}

		return 1.0f;
	};

	if (dijkstra.Run(mGraph, startX, startY, endX, endY, getCost))
	{
		const auto& closedList = dijkstra.GetClosedList();
		auto node = closedList.back();

		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	return path;
}

Path TileMap::FindPathAStar(int startX, int startY, int endX, int endY)
{
	Path path;
	AStar aStar;

	auto getCost = [](const GridBasedGraph::Node* node, const GridBasedGraph::Node* neighbor)->float
	{
		if (node->column != neighbor->column && node->row != neighbor->row)
		{
			return 1.7f;
		}

		return 1.0f;
	};
	auto getHerustic = [](const GridBasedGraph::Node* neighbor, const GridBasedGraph::Node* endNode)->float
	{
		float D = 1.0f;
		float dx = abs(neighbor->column - endNode->column);
		float dy = abs(neighbor->row - endNode->row);

		return D * (dx + dy);
	};

	if (aStar.Run(mGraph, startX, startY, endX, endY, getCost, getHerustic))
	{
		const auto& closedList = aStar.GetClosedList();
		auto node = closedList.back();

		while (node != nullptr)
		{
			path.push_back(GetPixelPosition(node->column, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}

	return path;
}

bool TileMap::IsBlocked(int x, int y) const
{
	if (x >= 0 && x < mColumns && y >= 0 && y < mRows)
	{
		const int index = ToIndex(x, y, mColumns);

		if (index < mMap.size())
		{
			int tile = mMap[index];
			return mTiles[tile].isBlocked;
		}
	}

	return true;
}

X::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
	return{
		(x + 0.5f) * mTileWidth,
		(y + 0.5f) * mTileHeight
	};
}

const AI::GridBasedGraph::Node* TileMap::GetClosestNode(int x, int y) const
{
	X::Math::Vector2 mousePos(x, y);
	const AI::GridBasedGraph::Node* clickedNode = nullptr;
	float closestDist = FLT_MAX;

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const auto node = mGraph.GetNode(c, r);
			float distanceSqr = X::Math::DistanceSqr(GetPixelPosition(node->column, node->row), mousePos);
			if (distanceSqr < closestDist)
			{
				closestDist = distanceSqr;
				clickedNode = node;
			}
		}
	}
	return clickedNode;
}
