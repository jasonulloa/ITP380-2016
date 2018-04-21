#include "Cannonball.h"
#include "Game.h"
#include "SphereCollision.h"

IMPL_ACTOR(Cannonball, Actor);

Cannonball::Cannonball(Game& game) : Actor(game) {
	mCannonballMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mCannonball = texture.Load<Mesh>("Meshes/Cannonball.itpmesh2");
	mCannonballMeshComponent->SetMesh(mCannonball);
	mCannonballMeshComponent->SetMeshTexture(0);
	auto mCannonballMoveComponent = MoveComponent::Create(*this, Component::PreTick);
	mCannonballMoveComponent->SetLinearSpeed(300.0f);
	mCannonballMoveComponent->SetLinearAxis(1.0f);
	game.GetGameTimers().SetTimer(mMissTimer, this, &Cannonball::RemoveCannonball, 3.0f);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(texture.Load<Mesh>("Meshes/Cannonball.itpmesh2"));
	coll->SetScale(0.9f);
}

void Cannonball::RemoveCannonball() {
	if (this->IsAlive()) {
		this->SetIsAlive(false);
	}
}