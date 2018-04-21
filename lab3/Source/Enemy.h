#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AudioComponent.h"

class Enemy : public Actor {
	DECL_ACTOR(Enemy, Actor);
public:
	Enemy(Game& game);
	void Slow();
	void Unslow();

	void BeginTouch(Actor& other) override;
	void BeginPlay() override;
	void EndPlay() override;
private:
	MoveComponentPtr mEnemyMoveComponent;
	MeshComponentPtr mEnemyMeshComponent;
	AudioComponentPtr mEnemyAudioComponent;
	MeshPtr mEnemy;
	SoundPtr mScream;
	int hitPoints;
};

DECL_PTR(Enemy);