#include "GameMode.h"
#include "Game.h"
#include "CannonTower.h"
#include "FrostTower.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game) : Actor(game) {
	mMoney = 300;
	mHealth = 5;
	mInputComponent = InputComponent::Create(*this, Component::PreTick);
	mAudioComponent = AudioComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mBuild = texture.Load<Sound>("Sounds/Building.wav");
	mError = texture.Load<Sound>("Sounds/ErrorSound.wav");
	mSelectedTile = nullptr;
}

void GameMode::BeginPlay() {
	for (float y = 225.0f; y > -225.0f; y -= 50.0f) {
		std::vector<TilePtr> temp;
		for (float x = -425.0f; x < 475.0f; x += 50.0f) {
			Vector3 tilePos(x, y, 0.0f);
			auto tile = Tile::Spawn(mGame);
			tile->SetPosition(tilePos);
			tile->SetTileType(Default);
			temp.emplace_back(tile);
		}
		grid.emplace_back(temp);
	}

	grid[3][0]->SetTileType(Green);
	grid[4][0]->SetTileType(Green);
	grid[4][1]->SetTileType(Green);
	grid[5][0]->SetTileType(Green);
	grid[4][17]->SetTileType(Red);
	grid[4][17]->SetCollider();

	mGame.GetInput().BindAction("Select", IE_Pressed, this, &GameMode::SelectTile);
	mGame.GetInput().BindAction("Build Cannon", IE_Pressed, this, &GameMode::BuildCannon);
	mGame.GetInput().BindAction("Build Frost", IE_Pressed, this, &GameMode::BuildFrost);

	mSpawnerPtr = Spawner::Spawn(mGame);
	mHealthHUD = HUD::Spawn(mGame);
	mMoneyHUD = HUD::Spawn(mGame);
	mMessageHUD = HUD::Spawn(mGame);

	auto healthOffset = Actor::Spawn(mGame);
	Vector3 healthOffsetPos(-450.0f, 350.0f, 0.0f);
	healthOffset->SetPosition(healthOffsetPos);
	healthOffset->AddChild(mHealthHUD);
	auto moneyOffset = Actor::Spawn(mGame);
	Vector3 moneyOffsetPos(-450.0f, 325.0f, 0.0f);
	moneyOffset->SetPosition(moneyOffsetPos);
	moneyOffset->AddChild(mMoneyHUD);
	auto messageOffset = Actor::Spawn(mGame);
	Vector3 messageOffsetPos(-200.0f, 25.0f, 0.0f);
	messageOffset->SetPosition(messageOffsetPos);
	messageOffset->AddChild(mMessageHUD);
}

void GameMode::SpawnFirstWave() {
	mSpawnerPtr->SpawnWave();
	mHealthHUD->SetHP(mHealth);
	mHealthHUD->UpdateHPText();
	mMoneyHUD->SetMoney(mMoney);
	mMoneyHUD->UpdateMoneyText();
}

void GameMode::SelectTile() {
	int row, col;
	Game& game = GetGame();
	Vector2 mouse = game.GetInput().GetMousePos();
	if ((mouse.y >= 133 && mouse.y <= 583) && (mouse.x >= 62 && mouse.x <= 962)) {
		row = (mouse.y - 133) / 50;
		col = (mouse.x - 62) / 50;
		if (!((row == 3 && col == 0) || (row == 4 && (col == 0 || col == 1 || col == 17)) || (row == 5 && col == 0))) {
			if (mSelectedTile == nullptr) {
				mSelectedTile = grid[row][col];
				mSelectedTilePos.x = col;
				mSelectedTilePos.y = row;
				if (mSelectedTile->GetTileType() == DefaultPath) {
					mSelectedTile->SetTileType(SelectedPath);
				}
				else {
					mSelectedTile->SetTileType(Selected);
				}
			}
			else if (mSelectedTile != grid[row][col]) {
				if (mSelectedTile->GetTileType() == SelectedPath) {
					mSelectedTile->SetTileType(DefaultPath);
				}
				else {
					mSelectedTile->SetTileType(Default);
				}
				mSelectedTile = grid[row][col];
				mSelectedTilePos.x = col;
				mSelectedTilePos.y = row;
				if (mSelectedTile->GetTileType() == DefaultPath) {
					mSelectedTile->SetTileType(SelectedPath);
				}
				else {
					mSelectedTile->SetTileType(Selected);
				}
			}
		}
		else {
			if (mSelectedTile != nullptr) {
				if (mSelectedTile->GetTileType() == SelectedPath) {
					mSelectedTile->SetTileType(DefaultPath);
				}
				else {
					mSelectedTile->SetTileType(Default);
				}
				mSelectedTile = nullptr;
			}
		}
	}
	else {
		if (mSelectedTile != nullptr) {
			if (mSelectedTile->GetTileType() == SelectedPath) {
				mSelectedTile->SetTileType(DefaultPath);
			}
			else {
				mSelectedTile->SetTileType(Default);
			}
			mSelectedTile = nullptr;
		}
	}
}

void GameMode::BuildCannon() {
	Game& game = GetGame();
	if (mSelectedTile != nullptr && mSelectedTile->GetTower() == nullptr && mMoney >= 100 && mHealth > 0) {
		game.GetNavWorld()->GetNodeGrid()[mSelectedTilePos.y][mSelectedTilePos.x]->isBlocked = true;
		if(game.GetNavWorld()->TryFindPath()){
			Vector3 pos = mSelectedTile->GetPosition();
			auto tower = Tower::Spawn(game);
			tower->SetPosition(pos);
			auto cannon = CannonTower::SpawnAttached(*tower);
			mSelectedTile->SetTower(tower);
			mMoney -= 100;
			GetMoneyHUD()->SetMoney(mMoney);
			GetMoneyHUD()->UpdateMoneyText();
			mAudioComponent->PlaySound(mBuild, 0);
		}
		else {
			TimerHandle handle;
			mMessageHUD->SetMessage("Cannot block off enemy path.");
			mMessageHUD->PrintHUDMessage();
			game.GetGameTimers().SetTimer(handle, this, &GameMode::ClearMessageHUD, 2.0f);
			game.GetNavWorld()->GetNodeGrid()[mSelectedTilePos.y][mSelectedTilePos.x]->isBlocked = false;
			mAudioComponent->PlaySound(mError, 0);
		}
	}
	else {
		if (mMoney < 100 && mSelectedTile->GetTower() == nullptr) {
			TimerHandle handle;
			mMessageHUD->SetMessage("Not enough money to build.");
			mMessageHUD->PrintHUDMessage();
			game.GetGameTimers().SetTimer(handle, this, &GameMode::ClearMessageHUD, 2.0f);
		}
		mAudioComponent->PlaySound(mError, 0);
	}
}

void GameMode::BuildFrost() {
	Game& game = GetGame();
	if (mSelectedTile != nullptr && mSelectedTile->GetTower() == nullptr && mMoney >= 200 && mHealth > 0) {
		game.GetNavWorld()->GetNodeGrid()[mSelectedTilePos.y][mSelectedTilePos.x]->isBlocked = true;
		if (game.GetNavWorld()->TryFindPath()) {
			Vector3 pos = mSelectedTile->GetPosition();
			auto tower = Tower::Spawn(game);
			tower->SetPosition(pos);
			auto frost = FrostTower::SpawnAttached(*tower);
			mSelectedTile->SetTower(tower);
			mMoney -= 200;
			GetMoneyHUD()->SetMoney(mMoney);
			GetMoneyHUD()->UpdateMoneyText();
			mAudioComponent->PlaySound(mBuild, 0);
		}
		else {
			TimerHandle handle;
			mMessageHUD->SetMessage("Cannot block off enemy path.");
			mMessageHUD->PrintHUDMessage();
			game.GetGameTimers().SetTimer(handle, this, &GameMode::ClearMessageHUD, 2.0f);
			game.GetNavWorld()->GetNodeGrid()[mSelectedTilePos.y][mSelectedTilePos.x]->isBlocked = false;
			mAudioComponent->PlaySound(mError, 0);
		}
	}
	else {
		if (mMoney < 200 && mSelectedTile->GetTower() == nullptr) {
			TimerHandle handle;
			mMessageHUD->SetMessage("Not enough money to build.");
			mMessageHUD->PrintHUDMessage();
			game.GetGameTimers().SetTimer(handle, this, &GameMode::ClearMessageHUD, 2.0f);
		}
		mAudioComponent->PlaySound(mError, 0);
	}
}

void GameMode::ClearMessageHUD() {
	mMessageHUD->SetMessage("");
	mMessageHUD->PrintHUDMessage();
}