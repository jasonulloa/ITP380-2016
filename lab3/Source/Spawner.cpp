#include "Spawner.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

IMPL_ACTOR(Spawner, Actor);

Spawner::Spawner(Game& game) : Actor(game) {
	mSpawnCount = 0;
	mLevel = 0;
}

void Spawner::SpawnWave() {
	Game& game = GetGame();
	if (game.GetGameMode()->GetHealth() > 0) {
		mGame.GetGameTimers().ClearTimer(mWaveHandle);
		mGame.GetGameTimers().SetTimer(mSpawnHandle, this, &Spawner::SpawnEnemy, 1.0f, true);
		mLevel++;
	}
}

void Spawner::SpawnEnemy() {
	Vector3 start(-425.0f, 25.0f, 0.0f);
	Game& game = GetGame();
	auto foe = Enemy::Spawn(game);
	foe->SetPosition(start);
	foe->SetScale(1.0f);
	mSpawnCount++;

	if (mSpawnCount == 5 * mLevel) {
		mGame.GetGameTimers().SetTimer(mWaveHandle, this, &Spawner::SpawnWave, 5.0f);
		mGame.GetGameTimers().ClearTimer(mSpawnHandle);
		mSpawnCount = 0;
	}
}