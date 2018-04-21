#include "Asteroid.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "Random.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game) : Actor(game) {
	auto mesh = MeshComponent::Create(*this); 
	AssetCache& texture = game.GetAssetCache();
	mesh->SetMesh(texture.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2"));
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	auto move = MoveComponent::Create(*this, Component::PreTick); 
	move->SetLinearSpeed(150.0f); 
	move->SetLinearAxis(1.0f);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(texture.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2"));
	coll->SetScale(0.9f);
}