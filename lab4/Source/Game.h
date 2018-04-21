// Game.h
// Contains the core game functionality
// such as the game loop

#pragma once
#include "Renderer.h"
#include "FrameTimer.h"
#include "World.h"
#include "AssetCache.h"
#include "InputManager.h"
#include "GameTimers.h"
#include "PhysWorld.h"
#include "GameMode.h"

class Game
{
public:
	Game();
	~Game();
	bool Init();
	void RunLoop();
	void Quit();

	Renderer& GetRenderer() { return mRenderer; }
	World& GetWorld() { return mWorld; }
	AssetCache& GetAssetCache() { return mAssetCache; }
	PhysWorld& GetPhysWorld() { return mPhysWorld; }
	InputManager& GetInput() { return mInput; }
	GameTimerManager& GetGameTimers() { return mTimerManager; }
	GameModePtr GetGameMode() { return mGameMode; }
private:
	void StartGame();

	void AddInputMappings();
	void ProcessInput();
	void HandleKeyPressed(int key);
	void HandleKeyReleased(int key);

	void Tick();
	void GenerateOutput();

	Renderer mRenderer;
	FrameTimer mTimer;
	World mWorld;
	AssetCache mAssetCache;
	PhysWorld mPhysWorld;
	InputManager mInput;
	GameTimerManager mTimerManager;
	GameModePtr mGameMode;

	bool mShouldQuit;
};
