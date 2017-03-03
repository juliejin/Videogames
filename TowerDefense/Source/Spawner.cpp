//
//  Spawner.cpp
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Spawner.h"
#include "Game.h"
#include "Enemy.h"

IMPL_ACTOR(Spawner,Actor);

Spawner::Spawner(Game& game) : Actor(game)
{
    waveNum = 0;
    enemyNum = 0;
    wavePause = 5;
    pause = 5;
}

Spawner::~Spawner()
{
    
}

void Spawner::BeginPlay()
{
    PauseWave();
}

void Spawner::SpawnWave()
{
    waveNum++;
    wavePause = 5 *waveNum +pause;
    GetGame().getTimerManager().ClearTimer(mWaveTimerHandle);
    GetGame().getTimerManager().SetTimer(mWaveTimerHandle, this, &Spawner::SpawnEnemies, 1.0f, true);
}

void Spawner::PauseWave(){
    if(pause == 0){
        pause = 5;
        GetGame().getTimerManager().ClearTimer(mWaveTimerHandle);
        SpawnWave();
    }
    else{
        pause--;
        GetGame().getTimerManager().AddTime(mWaveTimerHandle, 1.0f);
        wavePause = pause;
        if(pause == 4){
            GetGame().getTimerManager().SetTimer(mWaveTimerHandle, this, &Spawner::PauseWave, 1.0f, true);
        }
    }
}

void Spawner::SpawnEnemies()
{
    if(enemyNum > waveNum * 5){
        enemyNum = 0;
        GetGame().getTimerManager().ClearTimer(mWaveTimerHandle);
        PauseWave();
    }
    else{
        EnemyPtr enemy = Enemy::Spawn(mGame);
       
        enemyNum++;
        wavePause--;
    }
}
