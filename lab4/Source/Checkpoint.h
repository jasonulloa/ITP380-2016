#pragma once
#include "Actor.h"

class Checkpoint : public Actor {
	DECL_ACTOR(Checkpoint, Actor);
public:
	Checkpoint(Game& game);
};

DECL_PTR(Checkpoint);