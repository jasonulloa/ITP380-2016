#pragma once
#include "Actor.h"

class Arrow : public Actor {
	DECL_ACTOR(Arrow, Actor);
public:
	Arrow(Game& game);

	void Tick(float deltaTime) override;
	void BeginPlay() override;

	void SetPlayer(ActorPtr player) { mPlayer = player; }
	void SetNextCheckpointPos(Vector3 nextPoint) { mNextCheckpointPos = nextPoint; }
	Vector3 UpdateWorldPosition();
private:
	ActorPtr mPlayer;
	Vector3 mNextCheckpointPos;
};

DECL_PTR(Arrow);