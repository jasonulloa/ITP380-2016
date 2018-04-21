#pragma once
#include "Tile.h"

struct PathNode
{
	typedef std::shared_ptr<PathNode> PathNodePtr;
	std::vector<PathNodePtr> adjacencyList;
	TilePtr mThisTile;
	Vector2 gridPos;
	PathNodePtr mParentNode;
	float fx, gx, hx;
	bool isBlocked;
};

DECL_PTR(PathNode);