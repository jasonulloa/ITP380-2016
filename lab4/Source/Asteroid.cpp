#include "Asteroid.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"

IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game) : Actor(game) {
	auto mesh = MeshComponent::Create(*this);
	SetScale(0.1f);
	AssetCache& texture = game.GetAssetCache();
	mesh->SetMesh(texture.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2"));
}