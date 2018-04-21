#pragma once
#include "Tower.h"
#include "AudioComponent.h"
#include "GameTimers.h"

class FrostTower : public Tower {
	DECL_ACTOR(FrostTower, Tower);
public:
	FrostTower(Game& game);
	void FindEnemiesInRange();
private:
	MeshComponentPtr mFrostMeshComponent;
	AudioComponentPtr mFrostAudioComponent;
	MeshPtr mFrost;
	SoundPtr mFreeze;
	TimerHandle mFrostTimer;
};

DECL_PTR(FrostTower);