#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "Spawner.h"
#include "Tile.h"
#include "HUD.h"


class GameMode : public Actor
{
    DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void BeginPlay() override;
	void EndPlay() override;

    // Get the position that enemies should spawn from
	const Vector3& GetSpawnPos() const;

    // Handle mouse click selection
	void HandleSelect();

    // Return the requested tile at the (x, y) index
    // in the grid of tiles
	TilePtr GetTile(const Vector2& gridPos);
    
    void CreateCannonTower();
    void CreateFrostTower();
    int GetMoney() { return mMoney; };
    int GetHealth() { return mHealth; };
    
private:
    int mHealth;
    int mMoney;
    // Create the tiles
	void CreateTiles();

    // All of the tiles in the grid
	std::vector<std::vector<TilePtr>> mTiles;
    // Current selected tile, or nullptr if none
	TilePtr mSelectedTile;
    SpawnerPtr mSpawnerPtr;
    
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mBuildingSoundPtr;
    SoundPtr mErrorSoundPtr;
    HUDPtr hud;
};
DECL_PTR(GameMode);
