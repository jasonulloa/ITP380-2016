#include "FrostTower.h"
#include "Game.h"
#include "World.h"
#include "Enemy.h"
#include <vector>

IMPL_ACTOR(FrostTower, Tower);

FrostTower::FrostTower(Game& game) : Tower(game) {
	mFrostMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mFrost = texture.Load<Mesh>("Meshes/Frost.itpmesh2");
	mFrostMeshComponent->SetMesh(mFrost);
	mFrostMeshComponent->SetMeshTexture(0);
	mFrostAudioComponent = AudioComponent::Create(*this);
	mFreeze = texture.Load<Sound>("Sounds/Freeze.wav");
	mGame.GetGameTimers().SetTimer(mFrostTimer, this, &FrostTower::FindEnemiesInRange, 2.0f, true);
}

void FrostTower::FindEnemiesInRange() {
	Vector3 position = this->GetWorldTransform().GetTranslation();
	std::vector<Enemy*> foes = this->GetGame().GetWorld().GetEnemiesInRange(position, 150.0f);

	TimerHandle freeze;
	for (Enemy* foe : foes) {
		foe->Slow();
		mGame.GetGameTimers().SetTimer(freeze, foe, &Enemy::Unslow, 1.0f);
	}
	mFrostAudioComponent->PlaySound(mFreeze, 0);
}