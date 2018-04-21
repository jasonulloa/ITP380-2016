#include "NavWorld.h"
#include "Game.h"
#include "GameMode.h"

IMPL_ACTOR(NavWorld, Actor);

NavWorld::NavWorld(Game& game) : Actor(game) {
	std::vector< std::vector<TilePtr> > grid = game.GetGameMode()->GetTileGrid();

	for (int y = 0; y < 9; ++y) {
		std::vector<PathNodePtr> temp;
		for (int x = 0; x < 18; ++x) {
			PathNodePtr node = std::make_shared<PathNode>();
			node->mThisTile = grid[y][x];
			node->gridPos.x = x;
			node->gridPos.y = y;
			node->mParentNode = nullptr;
			node->fx = 0.0f;
			node->gx = 0.0f;
			node->hx = 0.0f;
			node->isBlocked = false;
			temp.emplace_back(node);
		}
		nodeGrid.emplace_back(temp);
	}

	mStartNode = nodeGrid[4][17];
	mEndNode = nodeGrid[4][0];

	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < 18; ++x) {
			if (y > 0) {
				nodeGrid[y][x]->adjacencyList.emplace_back(nodeGrid[y - 1][x]);
			}
			if (x > 0) {
				nodeGrid[y][x]->adjacencyList.emplace_back(nodeGrid[y][x - 1]);
			}
			if (y < 8) {
				nodeGrid[y][x]->adjacencyList.emplace_back(nodeGrid[y + 1][x]);
			}
			if (x < 17) {
				nodeGrid[y][x]->adjacencyList.emplace_back(nodeGrid[y][x + 1]);
			}
		}
	}
}

bool NavWorld::TryFindPath() {
	std::unordered_set<PathNodePtr> open_set;
	std::unordered_set<PathNodePtr> closed_set;

	PathNodePtr currentNode = mStartNode;
	do {
		for (PathNodePtr node : currentNode->adjacencyList) {
			auto iterc = closed_set.find(node);
			auto itero = open_set.find(node);
			
			if (iterc != closed_set.end()) {
				continue;
			}
			else if (itero != open_set.end()) {
				float new_gx = currentNode->gx + 1.0f;
				if (new_gx < node->gx) {
					node->mParentNode = currentNode;
					node->gx = new_gx;
					node->fx = node->gx + node->hx;
				}
			}
			else {
				if (!node->isBlocked) {
					node->mParentNode = currentNode;
					node->hx = Math::Abs(node->gridPos.x - mEndNode->gridPos.x) + Math::Abs(node->gridPos.y - mEndNode->gridPos.y);
					node->gx = currentNode->gx + 1.0f;
					node->fx = node->gx + node->hx;
					open_set.emplace(node);
				}
			}
		}

		if (open_set.empty()) {
			return false;
		}

		PathNodePtr nextNode = nullptr;
		for (PathNodePtr node : open_set) {
			if (nextNode != nullptr) {
				if (node->fx < nextNode->fx) {
					nextNode = node;
				}
			}
			else {
				nextNode = node;
			}
		}
		currentNode = nextNode;

		auto itero = open_set.find(nextNode);
		open_set.erase(itero);
		closed_set.emplace(nextNode);
	} while (currentNode != mEndNode);

	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < 18; ++x) {
			TextureType type = nodeGrid[y][x]->mThisTile->GetTileType();
			if (type == DefaultPath) {
				nodeGrid[y][x]->mThisTile->SetTileType(Default);
			}
			else if (type == SelectedPath) {
				nodeGrid[y][x]->mThisTile->SetTileType(Selected);
			}
			else if (type == GreenPath) {
				nodeGrid[y][x]->mThisTile->SetTileType(Green);
			}
			else if (type == RedPath) {
				nodeGrid[y][x]->mThisTile->SetTileType(Red);
			}
		}
	}

	do {
		TextureType type = currentNode->mThisTile->GetTileType();
		if (type == Default) {
			currentNode->mThisTile->SetTileType(DefaultPath);
		}
		else if (type == Selected) {
			currentNode->mThisTile->SetTileType(SelectedPath);
		}
		else if (type == Green) {
			currentNode->mThisTile->SetTileType(GreenPath);
		}
		else if (type == Red) {
			currentNode->mThisTile->SetTileType(RedPath);
		}
		currentNode = currentNode->mParentNode;
	} while (currentNode != mStartNode);

	currentNode->mThisTile->SetTileType(RedPath);

	return true;
}