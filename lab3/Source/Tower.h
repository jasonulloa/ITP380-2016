#pragma once
#include "Actor.h"
#include "MeshComponent.h"

class Tower : public Actor {
	DECL_ACTOR(Tower, Actor);
public:
	Tower(Game& game);
private:
	MeshComponentPtr mTowerMeshComponent;
	MeshPtr mTowerBase;
};

DECL_PTR(Tower);