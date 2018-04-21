#pragma once
#include "Actor.h"
#include "Tile.h"
#include "InputComponent.h"
#include "AudioComponent.h"
#include "Spawner.h"
#include "HUD.h"

class GameMode : public Actor {
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void BeginPlay() override;
	void SpawnFirstWave();
	void SelectTile();
	void BuildCannon();
	void BuildFrost();
	std::vector< std::vector<TilePtr> > GetTileGrid() { return grid; }
	int& GetMoney() { return mMoney; }
	void SetMoney(int cash) { mMoney = cash; }
	int& GetHealth() { return mHealth; }
	void SetHealth(int health) { mHealth = health; }
	HUDPtr GetHealthHUD() { return mHealthHUD; }
	HUDPtr GetMoneyHUD() { return mMoneyHUD; }
	HUDPtr GetMessageHUD() { return mMessageHUD; }
	void ClearMessageHUD();
private:
	int mMoney;
	int mHealth;
	std::vector< std::vector<TilePtr> > grid;
	TilePtr mSelectedTile;
	Vector2 mSelectedTilePos;
	InputComponentPtr mInputComponent;
	AudioComponentPtr mAudioComponent;
	SpawnerPtr mSpawnerPtr;
	SoundPtr mBuild;
	SoundPtr mError;
	HUDPtr mHealthHUD;
	HUDPtr mMoneyHUD;
	HUDPtr mMessageHUD;
};

DECL_PTR(GameMode);