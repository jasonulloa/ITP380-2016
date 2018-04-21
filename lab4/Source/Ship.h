#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "MeshComponent.h"
#include "AudioComponent.h"
#include "CameraComponent.h"

class Ship : public Actor {
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& game);
	
	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void BeginTouch(Actor& other) override;

	void SetGameOver(bool gameOver) { isGameOver = gameOver; }
	InputComponentPtr& GetInputComponent() { return mInputComponent; }
	void Recenter();
private:
	bool isGameOver;
	InputComponentPtr mInputComponent;
	MeshComponentPtr mMeshComponent;
	AudioComponentPtr mAudioComponent;
	CameraComponentPtr mCameraComponent;
	MeshPtr mSpaceship;
	SoundPtr mLaser;
	SoundPtr mEngine;
	SoundCue mSoundCue;
};

DECL_PTR(Ship);