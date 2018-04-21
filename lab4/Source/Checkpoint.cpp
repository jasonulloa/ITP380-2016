#include "Checkpoint.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Checkpoint, Actor);

Checkpoint::Checkpoint(Game& game) : Actor(game) {
	auto mesh = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mesh->SetMesh(texture.Load<Mesh>("Meshes/Checkpoint.itpmesh2"));
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(texture.Load<Mesh>("Meshes/Checkpoint.itpmesh2"));
	coll->SetScale(0.75f);
}