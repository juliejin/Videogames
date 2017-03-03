#include "GameMode.h"
#include "Game.h"
#include "SphereCollision.h"
//#include "CannonTower.h"
//#include "FrostTower.h"
//#include "NavWorld.h"
#include "Asteroid.h"
#include "Random.h"


IMPL_ACTOR(GameMode, Actor);

//const int NUM_COLS = 18;
//const int NUM_ROWS = 9;
//const float XOFFSET = -425.0f;
//const float YOFFSET = 200.0f;

GameMode::GameMode(Game& game)
	:Super(game)
{
    //mSelectedTile= nullptr;
   // mAudioComponentPtr = AudioComponent::Create(*this);
    //mBuildingSoundPtr = mGame.GetAssetCache().Load<Sound>("Sounds/Building.wav");
    //mErrorSoundPtr = mGame.GetAssetCache().Load<Sound>("Sounds/ErrorSound.wav");
    mAudioComponentPtr = AudioComponent::Create(*this);
    mSoundPtr = mGame.GetAssetCache().Load<Sound>("Sounds/Checkpoint.wav");
    score = 0.0f;
}

void GameMode::BeginPlay()
{
	Super::BeginPlay();

	//CreateTiles();
    
	//mGame.getInput().BindAction("Select", IE_Pressed, this, &GameMode::HandleSelect);
    
    //auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/Peasant.itpmesh2");
    //SphereCollisionPtr mSphereCollisionPtr = SphereCollision::Create(*mTiles[NUM_ROWS/2][NUM_COLS-1]);
   // mSphereCollisionPtr->RadiusFromMesh(mesh);
   // mSphereCollisionPtr->SetScale(0.5f);
    
    //mGame.getInput().BindAction("Cannon", IE_Pressed, this, &GameMode::CreateCannonTower);
    //mGame.getInput().BindAction("Frost", IE_Pressed, this, &GameMode::CreateFrostTower);
    
    //NavWorld& navWorld = mGame.GetNavWorld();
    //navWorld.Init(mTiles);
    //navWorld.setStartNode(4, 0);
    //navWorld.setEndNode(4, 17);
    //navWorld.TryFindPath();
    //mSpawnerPtr = Spawner::Spawn(mGame);
    
    const int NUM_ASTEROIDS = 500;
    Vector3 minVec(-5000.f, -5000.f, -5000.f);
    Vector3 maxVec(5000.f, 5000.f, 5000.f);
    for (int i = 0; i < NUM_ASTEROIDS; i++){
        auto ast = Asteroid::Spawn(mGame);
        ast->SetPosition(Random::GetVector(minVec,maxVec));
        ast->SetScale(0.75f);
    }
    mShip = Ship::Spawn(mGame);
    hud = HUD::Spawn(mGame);

}



void GameMode::EndPlay()
{
	Super::EndPlay();
}

void GameMode::SpawnRandomCheckPoint()
{
    Vector3 ShipPos = mShip->GetPosition();
    float range = 1000.0f + score;
    Vector3 max(range, range, range);
    Vector3 min = ShipPos - max;
    max = ShipPos + max;
    Vector3 pos = Random::GetVector(min, max);
    mCheck = CheckPoint::Spawn(mGame);
    mCheck->SetPosition(pos);
    //mArrow->SetCheckpointPos(pos);
}

void GameMode::CollectCheckPoint()
{
    mAudioComponentPtr->PlaySound(mSoundPtr);
    SpawnRandomCheckPoint();
    score += 100.00f;
   // mHUD->UpdateScore(score);
    //time += 3;
  //  mHUD->UpdateTime(time);
}




