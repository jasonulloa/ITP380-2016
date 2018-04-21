#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "AudioComponent.h"
#include "GameTimers.h"
#include "Ship.h"
#include "Arrow.h"
#include "HUD.h"

class GameMode : public Actor {
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void Tick(float deltaTime) override;
	void BeginPlay() override;
	ShipPtr GetShipPtr() { return mShipPtr; }
	void CollectCheckpoint();
private:
	void SpawnCheckpoint();
	void GameOver();

	int mScore;
	int mTime;
	int mLevel;
	bool isTimeRemaining;
	Vector3 mNextCheckpointPos;
	InputComponentPtr mInputComponent;
	AudioComponentPtr mAudioComponent;
	TimerHandle gameTimer;
	SoundPtr mCheckpoint;
	ShipPtr mShipPtr;
	ArrowPtr mArrowPtr;
	HUDPtr mScoreHUD;
	HUDPtr mTimerHUD;
	HUDPtr mMessageHUD;
};

DECL_PTR(GameMode);