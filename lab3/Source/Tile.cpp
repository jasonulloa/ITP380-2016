#include "Tile.h"
#include "Game.h"
#include "SphereCollision.h"

IMPL_ACTOR(Tile, Actor);

Tile::Tile(Game& game) : Actor(game) {
	mMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mTile = texture.Load<Mesh>("Meshes/Tile.itpmesh2");
	mMeshComponent->SetMesh(mTile);
	mMeshComponent->SetMeshTexture(Default);
	mTowerPtr = nullptr;
}

void Tile::SetTileType(TextureType type) {
	mMeshComponent->SetMeshTexture(type);
	mTileType = type;
}

void Tile::SetCollider() {
	Game& game = GetGame();
	AssetCache& texture = game.GetAssetCache();
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(texture.Load<Mesh>("Meshes/Tile.itpmesh2"));
	coll->SetScale(0.2f);
}