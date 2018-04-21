#include "GameMode.h"
#include "Game.h"
#include "Asteroid.h"
#include "Random.h"
#include "Checkpoint.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Actor(game) {
	mScore = 0;
	mTime = 15;
	mLevel = 0;
	isTimeRemaining = true;
	mInputComponent = InputComponent::Create(*this, Component::PreTick);
	mAudioComponent = AudioComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mCheckpoint = texture.Load<Sound>("Sounds/Checkpoint.wav");
}

void GameMode::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	int count = mGame.GetGameTimers().GetRemainingTime(gameTimer);
	mTimerHUD->SetTimerText(count + 1);
	mTimerHUD->UpdateTimerText();
}

void GameMode::BeginPlay() {
	mShipPtr = Ship::Spawn(mGame);
	mArrowPtr = Arrow::Spawn(mGame);
	mArrowPtr->SetPlayer(mShipPtr);

	Vector3 minVec(-5000.0f, -5000.0f, -5000.0f);
	Vector3 maxVec(5000.0f, 5000.0f, 5000.0f);
	for (int i = 0; i < 500; i++) {
		auto ast = Asteroid::Spawn(mGame);
		ast->SetPosition(Random::GetVector(minVec, maxVec));
	}

	mScoreHUD = HUD::Spawn(mGame);
	mTimerHUD = HUD::Spawn(mGame);
	mMessageHUD = HUD::Spawn(mGame);
	mScoreHUD->SetPoints(mScore);
	mScoreHUD->UpdateScoreText();
	mTimerHUD->SetTimerText(mTime);
	mTimerHUD->UpdateTimerText();

	auto scoreOffset = Actor::Spawn(mGame);
	Vector3 scoreOffsetPos(-50.0f, 350.0f, 0.0f);
	scoreOffset->SetPosition(scoreOffsetPos);
	scoreOffset->AddChild(mScoreHUD);
	auto timerOffset = Actor::Spawn(mGame);
	Vector3 timerOffsetPos(-45.0f, 325.0f, 0.0f);
	timerOffset->SetPosition(timerOffsetPos);
	timerOffset->AddChild(mTimerHUD);
	auto messageOffset = Actor::Spawn(mGame);
	Vector3 messageOffsetPos(-130.0f, 25.0f, 0.0f);
	messageOffset->SetPosition(messageOffsetPos);
	messageOffset->AddChild(mMessageHUD);

	SpawnCheckpoint();

	mGame.GetGameTimers().SetTimer(gameTimer, this, &GameMode::GameOver, (float)mTime);
}

void GameMode::CollectCheckpoint() {
	if (isTimeRemaining) {
		mScore += 100;
		mLevel++;
		mGame.GetGameTimers().AddTime(gameTimer, 5.0f);
		int count = mGame.GetGameTimers().GetRemainingTime(gameTimer);
		mScoreHUD->SetPoints(mScore);
		mScoreHUD->UpdateScoreText();
		mTimerHUD->SetTimerText(count);
		mTimerHUD->UpdateTimerText();
		mAudioComponent->PlaySound(mCheckpoint, 0);
		SpawnCheckpoint();
	}
}

void GameMode::SpawnCheckpoint() {
	Vector3 shipPos = mShipPtr->GetPosition();
	Vector3 minVec(shipPos.x - 1000.0f - (100.0f * mLevel), shipPos.y - 1000.0f - (100.0f * mLevel), shipPos.z - 1000.0f - (100.0f * mLevel));
	Vector3 maxVec(shipPos.x + 1000.0f + (100.0f * mLevel), shipPos.y + 1000.0f + (100.0f * mLevel), shipPos.z + 1000.0f + (100.0f * mLevel));
	auto chkpt = Checkpoint::Spawn(mGame);
	mNextCheckpointPos = Random::GetVector(minVec, maxVec);
	chkpt->SetPosition(mNextCheckpointPos);
	mArrowPtr->SetNextCheckpointPos(mNextCheckpointPos);
}

void GameMode::GameOver() {
	isTimeRemaining = false;
	mShipPtr->SetGameOver(!isTimeRemaining);
	mMessageHUD->SetMessage("G A M E   O V E R");
	mMessageHUD->PrintHUDMessage();
}