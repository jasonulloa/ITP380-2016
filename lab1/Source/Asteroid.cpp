#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "Random.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game) : Actor(game) {
	auto sprite = SpriteComponent::Create(*this); 
	AssetCache& texture = game.GetAssetCache();
	sprite->SetTexture(texture.Load<Texture>("Textures/Asteroid.png"));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	auto move = MoveComponent::Create(*this, Component::PreTick); 
	move->SetLinearSpeed(150.0f); 
	move->SetLinearAxis(1.0f);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromTexture(texture.Load<Texture>("Textures/Asteroid.png"));
	coll->SetScale(0.9f);
}