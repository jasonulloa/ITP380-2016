#include "Tower.h"
#include "Game.h"

IMPL_ACTOR(Tower, Actor);

Tower::Tower(Game& game) : Actor(game) {
	mTowerMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mTowerBase = texture.Load<Mesh>("Meshes/TowerBase.itpmesh2");
	mTowerMeshComponent->SetMesh(mTowerBase);
	mTowerMeshComponent->SetMeshTexture(0);
}