#include "Game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "FontComponent.h"

Game::Game()
	:mRenderer(*this)
	,mAssetCache(*this, "Assets/")
	,mShouldQuit(false)
{

}

Game::~Game()
{
	mAssetCache.Clear();
	mWorld.RemoveAllActors();
	Mix_CloseAudio();
	SDL_Quit();
	mGameMode.reset();
	TTF_Quit();
}

bool Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL.");
		return false;
	}

	// Initialize Renderer
	if (!mRenderer.Init(1024, 768))
	{
		SDL_Log("Failed to initialize renderer.");
		return false;
	}

	//Initialize Audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		SDL_Log("Failed to initialize audio.");
		return false;
	}

	//Initialize the TTF engine
	TTF_Init();

	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();

	//Initialize input mappings
	AddInputMappings();

	// Run any code at game start
	StartGame();

	return true;
}

void Game::RunLoop()
{
	while (!mShouldQuit) {
		ProcessInput();
		Tick();
		GenerateOutput();
	}
}

void Game::Quit()
{
	mShouldQuit = true;
}

void Game::StartGame()
{
	mGameMode = GameMode::Spawn(*this);
}

void Game::AddInputMappings() {
	mInput.AddActionMapping("Quit", SDLK_ESCAPE);
	mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
	mInput.AddAxisMapping("Move", 'p', SDLK_SEMICOLON);
	mInput.AddAxisMapping("Yaw", 'a', 'd');
	mInput.AddAxisMapping("Pitch", 'w', 's');
	mInput.AddActionMapping("Recenter", 'r');
}

void Game::ProcessInput()
{
	// Poll events from SDL
	SDL_Event event; 
	while (SDL_PollEvent(&event)){
		switch (event.type){
			case SDL_QUIT:
				mShouldQuit = true;
				break;
			case SDL_KEYDOWN: 
				if (event.key.repeat == 0) { 
					HandleKeyPressed(event.key.keysym.sym); 
				} 
				break; 
			case SDL_KEYUP: 
				HandleKeyReleased(event.key.keysym.sym);
				break;
			default:
				// Ignore other events for now
				break;
		}
	}
}

void Game::HandleKeyPressed(int key)
{
	mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{
	mInput.HandleKeyReleased(key);
}

void Game::Tick()
{
	float time = mTimer.GetFrameTime(0.016666f);
	mTimerManager.Tick(time);
	mWorld.Tick(time);
	mPhysWorld.Tick(time);
}

void Game::GenerateOutput()
{
	mRenderer.RenderFrame();
}
