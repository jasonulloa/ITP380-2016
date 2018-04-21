#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

class Ship : public Actor {
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& game);

	void Tick(float deltaTime) override;

	MoveComponentPtr& GetMoveComponent() { return mMoveComponent; }
	void FireMissile(Game& game);
private:
	MoveComponentPtr mMoveComponent;
	SpriteComponentPtr mSpriteComponent;
	TexturePtr mSpaceship;
	TexturePtr mSpaceshipThrust;
};

DECL_PTR(Ship);