#include "Game.h"
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
//#include "Asteroid.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include "HUD.h"

Game::Game()
	:mRenderer(*this)
	,mAssetCache(*this, "Assets/")
	,mShouldQuit(false)
    ,gameOver(false)
{
    
}

Game::~Game()
{
	mAssetCache.Clear();
	mWorld.RemoveAllActors();
    Mix_CloseAudio();
    //TTF_Quit();
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

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)!=0){
        SDL_Log("Failed initialize audio");
        return false;
    }
	// Initialize RNG
    TTF_Init();
	Random::Init();

	// Start frame timer
	mTimer.Start();
    
     AddInputMappings();
    
    
	// Run any code at game start
	StartGame();

	return true;
}

void Game::RunLoop()
{
	
    while (!mShouldQuit) {
        // TODO
        ProcessInput();
        Tick();
        GenerateOutput();
    }
}

void Game::Quit()
{
    mShouldQuit = true;
	// TODO
}

void Game::StartGame()
{
    mGameModePtr =GameMode::Spawn(*this);
    //shipPtr = Ship::Spawn(*this);
    //shipPtr->SetRotation(Math::PiOver2);
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mShouldQuit = true;
                break;
            case SDL_KEYDOWN:
                if(event.key.repeat==0){
                    HandleKeyPressed(event.key.keysym.sym);
                }
                break;
            case SDL_KEYUP:
                HandleKeyReleased(event.key.keysym.sym);
                break;
          /*  case SDL_MOUSEBUTTONDOWN:
                HandleKeyPressed(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                HandleKeyReleased(event.button.button);
                break;*/
            default:
                // Ignore other events for now
                break;
        }
    }// TODO
}

void Game::HandleKeyPressed(int key)
{
    mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{
    mInput.HandleKeyReleased(key);
}

GameTimerManager& Game::getTimerManager(){
    return mTimerManager;
}

void Game::Tick()
{
   if (!gameOver) {
	float deltaTime = mTimer.GetFrameTime(0.016666f);
    mTimerManager.Tick(deltaTime);
    
    mWorld.Tick(deltaTime);// TODO
    mPhysWorld.Tick(deltaTime);
    }
}

void Game::GenerateOutput()
{
    mRenderer.RenderFrame();// TODO
}

void Game::AddInputMappings(){
    mInput.AddActionMapping("Quit", SDLK_ESCAPE);
   // mInput.AddActionMapping("Fire", SDLK_SPACE);
    mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
    mInput.AddAxisMapping("Move", 'p', SDLK_SEMICOLON);
    mInput.AddAxisMapping("Yaw", 'a', 'd');
    mInput.AddAxisMapping("Pitch", 'w', 's');
     mInput.AddActionMapping("Recenter", 'r');
}

InputManager& Game::getInput(){
    return mInput;
}

GameModePtr Game::GetGameMode(){
    return mGameModePtr;
}



