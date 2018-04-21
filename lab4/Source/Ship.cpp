#include "Ship.h"
#include "Game.h"
#include "Checkpoint.h"
#include "Random.h"
#include "SphereCollision.h"

IMPL_ACTOR(Ship, Actor);

Ship::Ship(Game& game) : Actor(game) {
	isGameOver = false;
	mMeshComponent = MeshComponent::Create(*this);
	mAudioComponent = AudioComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mSpaceship = texture.Load<Mesh>("Meshes/PlayerShip.itpmesh2");
	mEngine = texture.Load<Sound>("Sounds/ShipEngine.wav");
	mMeshComponent->SetMesh(mSpaceship);
	SetScale(1.0f);
	mInputComponent = InputComponent::Create(*this, Component::PreTick);
	mInputComponent->SetLinearSpeed(400.0f);
	mInputComponent->SetYawSpeed(Math::Pi);
	mInputComponent->SetPitchSpeed(Math::Pi);
	mSoundCue = mAudioComponent->PlaySound(mEngine, -1);
	mSoundCue.Pause();
	mCameraComponent = CameraComponent::Create(*this);
	mCameraComponent->SetCameraMoveComponent(mInputComponent);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mSpaceship);
	coll->SetScale(1.0f);
}

void Ship::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	if (isGameOver) {
		mInputComponent->SetLinearAxis(0.0f);
		SetIsPaused(true);
	}

	if (mInputComponent->GetLinearAxis() == 0.0f) {
		mSoundCue.Pause();
	}
	else {
		mSoundCue.Resume();
	}
}

void Ship::BeginPlay() {
	Game& game = GetGame();
	game.GetInput().BindAction("Recenter", IE_Pressed, this, &Ship::Recenter);
	mInputComponent->BindLinearAxis("Move");
	mInputComponent->BindYawAxis("Yaw");
	mInputComponent->BindPitchAxis("Pitch");
	mCameraComponent->CalculateIdealCameraPos();
	mCameraComponent->SetCameraToIdealPos();
}

void Ship::BeginTouch(Actor& other) {
	if (IsA<Checkpoint>(other)) {
		other.SetIsAlive(false);
		mGame.GetGameMode()->CollectCheckpoint();
	}
}

void Ship::Recenter() {
	mInputComponent->GetOwner().SetRotation(Quaternion::Identity);
	mCameraComponent->CalculateIdealCameraPos();
	mCameraComponent->SetCameraToIdealPos();
}