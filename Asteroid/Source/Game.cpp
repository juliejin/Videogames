#include "Game.h"
#include <SDL/SDL.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "Asteroid.h"
#include <SDL/SDL_mixer.h>

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
    /*auto actor = Actor::Spawn(*this);
    
    //actor->SetPosition(Vector3(-256.0f, -192.0f, 0.0f));
    //actor->SetRotation(Math::PiOver2);
    //actor->SetScale(0.5f);
    
    auto sprite = SpriteComponent::Create(*actor);
    auto texture = mAssetCache.Load<Texture>("Textures/Spaceship.png");
    sprite->SetTexture(texture);
    */
    
    const int NUM_ASTEROIDS = 10;
    Vector3 minVec(-512.0f, -384.0f, 0.0f);
    Vector3 maxVec(512.f, 384.f, 0.0f);
    
    for (int i=0; i<NUM_ASTEROIDS; i++) {
        auto ast = Asteroid::Spawn(*this);
        ast->SetPosition(Random::GetVector(minVec, maxVec));
        ast->SetScale(0.75f);
    }
    shipPtr = Ship::Spawn(*this);
    shipPtr->SetRotation(Math::PiOver2);

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
            default:
                // Ignore other events for now
                break;
        }
    }// TODO
}

void Game::HandleKeyPressed(int key)
{   /*
    if(key == 'w'){
        shipPtr->GetMoveComponent()->AddToLinearAxis(+1.0f);
    }
    if(key == 's'){
        shipPtr->GetMoveComponent()->AddToLinearAxis(-1.0f);
    }
    if(key == 'a'){
        shipPtr->GetMoveComponent()->AddToAngularAxis(+1.0f);
    }
    if(key == 'd'){
        shipPtr->GetMoveComponent()->AddToAngularAxis(-1.0f);
    }
    if(key == SDLK_SPACE){
        shipPtr->FireMissile(*this);
    }
	*/
    mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{/*
    if(key == 'w'){
        shipPtr->GetMoveComponent()->AddToLinearAxis(-1.0f);
    }
    if(key == 's'){
        shipPtr->GetMoveComponent()->AddToLinearAxis(+1.0f);
    }
    if(key == 'a'){
        shipPtr->GetMoveComponent()->AddToAngularAxis(-1.0f);
    }
    if(key == 'd'){
        shipPtr->GetMoveComponent()->AddToAngularAxis(+1.0f);
    }
	*/
    mInput.HandleKeyReleased(key);
}

GameTimerManager& Game::getTimerManager(){
    return mTimerManager;
}

void Game::Tick()
{
	float deltaTime = mTimer.GetFrameTime(0.016666f);
    mTimerManager.Tick(deltaTime);
    
    mWorld.Tick(deltaTime);// TODO
    mPhysWorld.Tick(deltaTime);
}

void Game::GenerateOutput()
{
    mRenderer.RenderFrame();// TODO
}

void Game::AddInputMappings(){
    mInput.AddActionMapping("Quit", SDLK_ESCAPE);
    mInput.AddActionMapping("Fire", SDLK_SPACE);
    mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
    mInput.AddAxisMapping("Move", 'w', 's');
    mInput.AddAxisMapping("Rotate", 'a', 'd');
}

InputManager& Game::getInput(){
    return mInput;
}




