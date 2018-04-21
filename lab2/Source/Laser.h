#pragma once
#include "Actor.h"
#include "AudioComponent.h"

class Laser : public Actor {
	DECL_ACTOR(Laser, Actor);
public:
	Laser(Game& game);
	void OnDieTimer();

	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void BeginTouch(Actor& other) override;
private:
	AudioComponentPtr mBoom;
	SoundPtr mAstDie;
};

DECL_PTR(Laser);
