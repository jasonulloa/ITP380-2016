#include "Enemy.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Tile.h"
#include "Cannonball.h"
#include "World.h"
#include "NavComponent.h"

IMPL_ACTOR(Enemy, Actor);

Enemy::Enemy(Game& game) : Actor(game) {
	hitPoints = 3;
	mEnemyMeshComponent = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mEnemy = texture.Load<Mesh>("Meshes/Peasant.itpmesh2");
	mEnemyMeshComponent->SetMesh(mEnemy);
	mEnemyMeshComponent->SetMeshTexture(0);
	SetRotation(0.0f);
	mEnemyMoveComponent = MoveComponent::Create(*this, Component::PreTick);
	mEnemyMoveComponent->SetLinearSpeed(60.0f);
	mEnemyMoveComponent->SetLinearAxis(1.0f);
	mEnemyAudioComponent = AudioComponent::Create(*this);
	mScream = texture.Load<Sound>("Sounds/WilhelmScream.wav");
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(texture.Load<Mesh>("Meshes/Peasant.itpmesh2"));
	coll->SetScale(0.7f);
	auto nav = NavComponent::Create(*this);
	nav->FollowPath(game.GetNavWorld()->GetNodeGrid()[4][0], game.GetNavWorld()->GetNodeGrid()[4][17]);
}

void Enemy::Slow() {
	if (IsAlive()) {
		mEnemyMoveComponent->SetLinearSpeed(30.0f);
		mEnemyMeshComponent->SetMeshTexture(1);
	}
}

void Enemy::Unslow() {
	if (IsAlive()) {
		mEnemyMoveComponent->SetLinearSpeed(60.0f);
		mEnemyMeshComponent->SetMeshTexture(0);
	}
}

void Enemy::BeginTouch(Actor& other) {
	if (IsAlive() && IsA<Tile>(other)) {
		SetIsAlive(false);
		int hp = GetGame().GetGameMode()->GetHealth();
		hp--;
		if (hp < 0) {
			hp = 0;
		}
		if (hp == 0) {
			GetGame().GetGameMode()->GetMessageHUD()->SetMessage("      G  A  M  E     O  V  E  R");
			GetGame().GetGameMode()->GetMessageHUD()->PrintHUDMessage();
		}
		GetGame().GetGameMode()->SetHealth(hp);
		GetGame().GetGameMode()->GetHealthHUD()->SetHP(hp);
		GetGame().GetGameMode()->GetHealthHUD()->UpdateHPText();
	}

	if (IsAlive() && IsA<Cannonball>(other)) {
		--hitPoints;
		other.SetIsAlive(false);
		if (hitPoints == 0) {
			SetIsAlive(false);
			int cash = GetGame().GetGameMode()->GetMoney();
			cash += 10;
			GetGame().GetGameMode()->SetMoney(cash);
			GetGame().GetGameMode()->GetMoneyHUD()->SetMoney(cash);
			GetGame().GetGameMode()->GetMoneyHUD()->UpdateMoneyText();
			mEnemyAudioComponent->PlaySound(mScream, 0);
		}
	}
}

void Enemy::BeginPlay() {
	Enemy* foe = this;
	Game& game = GetGame();
	game.GetWorld().AddEnemy(foe);
}

void Enemy::EndPlay() {
	Enemy* foe = this;
	Game& game = GetGame();
	game.GetWorld().RemoveEnemy(foe);
	game.GetGameTimers().ClearAllTimers(foe);
}