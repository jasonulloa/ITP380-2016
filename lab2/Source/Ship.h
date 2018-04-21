#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

class Ship : public Actor {
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& game);
	void OnRespawnShip();

	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void BeginTouch(Actor& other) override;

	InputComponentPtr& GetInputComponent() { return mInputComponent; }
	void SetCanFire(bool canFire) { mCanFire = canFire; }
	bool GetCanFire() { return mCanFire; }
	void FireMissile();
private:
	InputComponentPtr mInputComponent;
	MeshComponentPtr mMeshComponent;
	AudioComponentPtr mAudioComponent;
	MeshPtr mSpaceship;
	SoundPtr mLaser;
	SoundPtr mEngine;
	SoundPtr mShipDie;
	SoundCue mSoundCue;
	bool mCanFire;
};

DECL_PTR(Ship);