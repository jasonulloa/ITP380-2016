#include "NavComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include <algorithm>

IMPL_COMPONENT(NavComponent, MoveComponent);

NavComponent::NavComponent(Actor& owner) : MoveComponent(owner) {

}

void NavComponent::Tick(float deltaTime) {
	Game& game = mOwner.GetGame();
	mNextNode = GetNextNode(mCurrentNode);
	Vector3 currPos = mOwner.GetPosition();
	Vector3 nextPos = mNextNode->mThisTile->GetPosition();
	Vector3 currToNext = nextPos - currPos;
	float distX = nextPos.x - currPos.x;
	float distY = nextPos.y - currPos.y;
	float dist = Math::Sqrt(distX * distX + distY * distY);
	if (dist < 1.0f) {
		mCurrentNode = mNextNode;
		mNextNode = GetNextNode(mCurrentNode);
	}

	currToNext.Normalize();
	Vector3 crossprod = Cross(Vector3::UnitX, currToNext);
	float dotprod = Dot(currToNext, Vector3::UnitX);
	float angle = Math::Acos(dotprod);
	if (crossprod.z < 0.0f) {
		angle *= -1.0f;
	}
	mOwner.SetRotation(angle);

	Super::Tick(deltaTime);
}

void NavComponent::FollowPath(PathNodePtr start, PathNodePtr end) {
	mPath.emplace_back(start);
	mCurrentNode = start;
	PathNodePtr thisNode = start->mParentNode;
	mNextNode = thisNode;
	while (thisNode != end) {
		mPath.emplace_back(thisNode);
		thisNode = thisNode->mParentNode;
	}
	mPath.emplace_back(end);
}

PathNodePtr NavComponent::GetNextNode(PathNodePtr currNode) {
	PathNodePtr nextNode;
	auto iter = std::find(mPath.begin(), mPath.end(), currNode);
	++iter;
	nextNode = (*iter);
	return nextNode;
}