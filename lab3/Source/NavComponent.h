#pragma once
#include "MoveComponent.h"
#include "PathNode.h"
#include <list>

class NavComponent : public MoveComponent {
	DECL_COMPONENT(NavComponent, MoveComponent);
public:
	NavComponent(Actor& owner);

	void Tick(float deltaTime) override;

	void FollowPath(PathNodePtr start, PathNodePtr end);
	PathNodePtr GetNextNode(PathNodePtr currNode);
private:
	std::list<PathNodePtr> mPath;
	PathNodePtr mCurrentNode;
	PathNodePtr mNextNode;
};

DECL_PTR(NavComponent);