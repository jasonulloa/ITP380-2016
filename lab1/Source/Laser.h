#pragma once
#include "Actor.h"

class Laser : public Actor {
	DECL_ACTOR(Laser, Actor);
public:
	Laser(Game& game);

	void Tick(float deltaTime) override;
	void BeginTouch(Actor& other) override;
private:
	float TTL;
};

DECL_PTR(Laser);
