#pragma once
#include "Tower.h"
#include "AudioComponent.h"
#include "GameTimers.h"

class CannonTower : public Tower {
	DECL_ACTOR(CannonTower, Tower);
public:
	CannonTower(Game& game);
	void FindClosestEnemy();
private:
	MeshComponentPtr mCannonMeshComponent;
	AudioComponentPtr mCannonAudioComponent;
	MeshPtr mCannon;
	SoundPtr mCannonfire;
	TimerHandle mShootTimer;
};

DECL_PTR(CannonTower);