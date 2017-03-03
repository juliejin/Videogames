// Game.h
// Contains the core game functionality
// such as the game loop

#pragma once
#include "Renderer.h"
#include "FrameTimer.h"
#include "World.h"
#include "AssetCache.h"
#include "PhysWorld.h"
#include "Ship.h"
#include "InputManager.h"
#include "GameTimers.h"
#include "GameMode.h"
//#include "NavWorld.h"
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
    InputManager& getInput();
    void AddInputMappings();
    GameTimerManager& getTimerManager();
     GameModePtr GetGameMode();
   // NavWorld& GetNavWorld(){ return mNavWorld;}
    
private:
	void StartGame();
	
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
    
    ShipPtr shipPtr;
    
    InputManager mInput;
    //Game* mGame;
    
    GameTimerManager mTimerManager;
    GameModePtr mGameModePtr;
    
   // NavWorld mNavWorld;
    

	bool mShouldQuit;
};
