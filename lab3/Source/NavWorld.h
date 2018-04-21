#pragma once
#include "PathNode.h"
#include "Actor.h"

class NavWorld : public Actor {
	DECL_ACTOR(NavWorld, Actor);
public:
	NavWorld(Game& game);

	bool TryFindPath();
	std::vector< std::vector<PathNodePtr> >& GetNodeGrid() { return nodeGrid; }
private:
	std::vector< std::vector<PathNodePtr> > nodeGrid;
	PathNodePtr mStartNode;
	PathNodePtr mEndNode;
};

DECL_PTR(NavWorld);