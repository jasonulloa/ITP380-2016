#include "Laser.h"
#include "Game.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game& game) : Actor(game) {
	auto sprite = SpriteComponent::Create(*this);
	mBoom = AudioComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	sprite->SetTexture(texture.Load<Texture>("Textures/Laser.png"));
	mAstDie = texture.Load<Sound>("Sounds/AsteroidDie.wav");
	auto move = MoveComponent::Create(*this, Component::PreTick);
	move->SetLinearSpeed(600.0f);
	move->SetLinearAxis(1.0f);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromTexture(texture.Load<Texture>("Textures/Laser.png"));
	coll->SetScale(0.9f);
}

void Laser::OnDieTimer() {
	SetIsAlive(false);
}

void Laser::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}

void Laser::BeginPlay() {
	TimerHandle handle;
	mGame.GetGameTimers().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}

void Laser::BeginTouch(Actor& other) {
	Super::BeginTouch(other);

	if (IsAlive() && IsA<Asteroid>(other)) {
		Vector3 astPos = other.GetPosition();
		SetIsAlive(false);
		other.SetIsAlive(false);
		mBoom->PlaySound(mAstDie, 0);
		Game& game = GetGame();
		if (other.GetScale() > 0.25f) {
			for (int i = 0; i < 4; i++) {
				auto ast = Asteroid::Spawn(game);
				ast->SetPosition(astPos);
				ast->SetScale(0.25f);
			}
		}
	}
}