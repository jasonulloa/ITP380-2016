#include "CannonTower.h"
#include "Game.h"
#include "Cannonball.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& game) : Tower(game) {
	mCannonMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mCannon = texture.Load<Mesh>("Meshes/Cannon.itpmesh2");
	mCannonMeshComponent->SetMesh(mCannon);
	mCannonMeshComponent->SetMeshTexture(0);
	mCannonAudioComponent = AudioComponent::Create(*this);
	mCannonfire = texture.Load<Sound>("Sounds/CannonFire.wav");
	mGame.GetGameTimers().SetTimer(mShootTimer, this, &CannonTower::FindClosestEnemy, 1.0f, true);
}

void CannonTower::FindClosestEnemy() {
	Game& game = GetGame();
	Vector3 position = this->GetWorldTransform().GetTranslation();
	Enemy* foe = this->GetGame().GetWorld().GetClosestEnemy(position);

	if (foe != nullptr) {
		Vector3 foePos = foe->GetPosition();
		Vector3 CannonToFoe = foePos - position;
		CannonToFoe.Normalize();
		Vector3 crossprod = Cross(Vector3::UnitX, CannonToFoe);
		float dotprod = Dot(CannonToFoe, Vector3::UnitX);
		float angle = Math::Acos(dotprod);
		if (crossprod.z < 0.0f) {
			angle *= -1.0f;
		}
		SetRotation(angle);
		auto bang = Cannonball::Spawn(game);
		bang->SetPosition(position);
		bang->SetRotation(angle);
		mCannonAudioComponent->PlaySound(mCannonfire, 0);
	}
}