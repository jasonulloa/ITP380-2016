#include "Ship.h"
#include "Game.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Random.h"
#include "Sound.h"
#include "SphereCollision.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game) : Actor(game) {
	mCanFire = true;
	mMeshComponent = MeshComponent::Create(*this);
	mAudioComponent = AudioComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mSpaceship = texture.Load<Mesh>("Meshes/PlayerShip.itpmesh2");
	mLaser = texture.Load<Sound>("Sounds/Laser.wav");
	mEngine = texture.Load<Sound>("Sounds/ShipEngine.wav");
	mShipDie = texture.Load<Sound>("Sounds/ShipDie.wav");
	mMeshComponent->SetMesh(mSpaceship);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
	SetScale(0.5f);
	mInputComponent = InputComponent::Create(*this, Component::PreTick);
	mInputComponent->SetLinearSpeed(400.0f);
	mInputComponent->SetAngularSpeed(Math::TwoPi);
	mSoundCue = mAudioComponent->PlaySound(mEngine, -1);
	mSoundCue.Pause();
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mSpaceship);
	coll->SetScale(0.75f);
}

void Ship::OnRespawnShip() {
	SetPosition(Vector3(0.0, 0.0, 0.0));
	SetRotation(Math::PiOver2);
	mMeshComponent->SetIsVisible(true);
	SetCanFire(true);
	SetIsPaused(false);
}

void Ship::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (mInputComponent->GetLinearAxis() == 0.0f) {
		mSoundCue.Pause();
	}
	else {
		mSoundCue.Resume();
	}
}

void Ship::BeginPlay() {
	Game& game = GetGame();
	game.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
	mInputComponent->BindLinearAxis("Move");
	mInputComponent->BindAngularAxis("Rotate");
}

void Ship::BeginTouch(Actor& other) {
	if (!IsPaused() && IsA<Asteroid>(other)) {
		SetCanFire(false);
		if (mSoundCue.IsPlaying()) {
			mSoundCue.Pause();
		}
		mAudioComponent->PlaySound(mShipDie, 0);
		SetIsPaused(true);
		mMeshComponent->SetIsVisible(false);
		TimerHandle handle;
		mGame.GetGameTimers().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
	}
}

void Ship::FireMissile() {
	if (!GetCanFire()) {
		return;
	}
	Game& game = GetGame();
	auto pew = Laser::Spawn(game);
	Vector3 shipPos = GetPosition();
	float shipRot = GetRotation();
	pew->SetPosition(shipPos);
	pew->SetRotation(shipRot);
	mAudioComponent->PlaySound(mLaser, 0);
}