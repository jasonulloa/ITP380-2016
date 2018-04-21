#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "GameTimers.h"

class Cannonball : public Actor {
	DECL_ACTOR(Cannonball, Actor);
public:
	Cannonball(Game& game);
	void RemoveCannonball();
private:
	MeshComponentPtr mCannonballMeshComponent;
	MeshPtr mCannonball;
	TimerHandle mMissTimer;
};

DECL_PTR(Cannonball);