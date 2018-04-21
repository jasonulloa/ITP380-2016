#include "Ship.h"
#include "Game.h"
#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Random.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game) : Actor(game) {
	mSpriteComponent = SpriteComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mSpaceship = texture.Load<Texture>("Textures/Spaceship.png");
	mSpaceshipThrust = texture.Load<Texture>("Textures/SpaceshipWithThrust.png");
	mSpriteComponent->SetTexture(mSpaceship);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	mMoveComponent = MoveComponent::Create(*this, Component::PreTick);
	mMoveComponent->SetLinearSpeed(400.0f);
	mMoveComponent->SetAngularSpeed(Math::TwoPi);
}

void Ship::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (mMoveComponent->GetLinearAxis() == 0.0f) {
		mSpriteComponent->SetTexture(mSpaceship);
	}
	else {
		mSpriteComponent->SetTexture(mSpaceshipThrust);
	}
}

void Ship::FireMissile(Game& game) {
	auto pew = Laser::Spawn(game);
	Vector3 shipPos = GetPosition();
	float shipRot = GetRotation();
	pew->SetPosition(shipPos);
	pew->SetRotation(shipRot);
}