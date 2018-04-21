#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "Tower.h"

enum TextureType { Default, Selected, Green, Red, DefaultPath, SelectedPath, GreenPath, RedPath };

class Tile : public Actor {
	DECL_ACTOR(Tile, Actor);
public:
	Tile(Game& game);

	void SetTileType(TextureType type);
	TextureType GetTileType() { return mTileType; }
	void SetCollider();

	TowerPtr GetTower() { return mTowerPtr; }
	void SetTower(TowerPtr tower) { mTowerPtr = tower; }
private:
	MeshComponentPtr mMeshComponent;
	MeshPtr mTile;
	TextureType mTileType;
	TowerPtr mTowerPtr;
};

DECL_PTR(Tile);