#include "Game.h"
#include <SDL/SDL.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "Asteroid.h"

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
	SDL_Quit();
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

	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();

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
	const int NUM_ASTEROIDS = 10;

	Vector3 minVec(-512.0f, -384.0f, 0.0f); 
	Vector3 maxVec(512.f, 384.f, 0.0f); 
	for (int i = 0; i < NUM_ASTEROIDS; i++) { 
		auto ast = Asteroid::Spawn(*this); 
		ast->SetPosition(Random::GetVector(minVec, maxVec));
		ast->SetScale(0.75f); 
	}

	mShipPtr = Ship::Spawn(*this);
	mShipPtr->SetRotation(Math::PiOver2);
	
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
	MoveComponentPtr move = mShipPtr->GetMoveComponent();
	switch (key) {
		case 'w':
			move->AddToLinearAxis(1.0f);
			break;
		case 's':
			move->AddToLinearAxis(-1.0f);
			break;
		case 'a':
			move->AddToAngularAxis(1.0f);
			break;
		case 'd':
			move->AddToAngularAxis(-1.0f);
			break;
		case SDLK_SPACE:
			mShipPtr->FireMissile(*this);
		default:
			break;
	}
}

void Game::HandleKeyReleased(int key)
{
	MoveComponentPtr move = mShipPtr->GetMoveComponent();
	switch (key) {
		case 'w':
			move->AddToLinearAxis(-1.0f);
			break;
		case 's':
			move->AddToLinearAxis(1.0f);
			break;
		case 'a':
			move->AddToAngularAxis(-1.0f);
			break;
		case 'd':
			move->AddToAngularAxis(1.0f);
			break;
		default:
			break;
	}
}

void Game::Tick()
{
	float time = mTimer.GetFrameTime(0.016666f);
	mWorld.Tick(time);
	mPhysWorld.Tick(time);
}

void Game::GenerateOutput()
{
	mRenderer.RenderFrame();
}
