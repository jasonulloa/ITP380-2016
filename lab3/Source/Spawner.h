#pragma once
#include "Actor.h"
#include "GameTimers.h"

class Spawner : public Actor {
	DECL_ACTOR(Spawner, Actor);
public:
	Spawner(Game& game);
	void SpawnWave();
	void SpawnEnemy();
private:
	TimerHandle mSpawnHandle;
	TimerHandle mWaveHandle;
	int mSpawnCount;
	int mLevel;
};

DECL_PTR(Spawner);