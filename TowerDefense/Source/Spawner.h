//
//  Spawner.h
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "GameTimers.h"

class Spawner : public Actor
{
    DECL_ACTOR(Spawner, Actor);
public:
    Spawner(Game& game);
    ~Spawner();
    void BeginPlay() override;
    void SpawnWave();
    void PauseWave();
    void SpawnEnemies();
    
    int GetTime() {return wavePause;}
private:
    int waveNum;
    int wavePause;
    int pause;
    TimerHandle mWaveTimerHandle;
    int enemyNum;
};

DECL_PTR(Spawner);
